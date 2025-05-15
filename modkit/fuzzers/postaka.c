// Copyright (c) 2022, Team FirmWire
// SPDX-License-Identifier: BSD-3-Clause
#include <shannon.h>
#include <afl.h>

/*  0xc3a0 opped LTE RRC messages have coarse grained the following structure:
 *      |------------|
 * 0x00 |  op        |
 *      |------------|
 * 0x04 |  size      |
 *      |------------| <- end of qiem_header
 * 0x08 |  UNUSED    |
 *      |------------|
 * 0x0c |  pdu type  | ## radio bearer
 *      |------------|
 * 0x10 |  pl_size   |
 *      |------------|
 * 0x14 |  asn_pl *  |
 *      |------------|
 *
 * IMPORTANT: the structure changes with other OPs!
 *
 */

const char TASK_NAME[] = "AFL_LTE_RRC\0";
struct qitem_lte_rrc {
  struct qitem_header header;
  uint32_t pdu_type;
  uint32_t pl_size;
  char * asn_pl;
} PACKED;

static uint32_t qid;
static struct pal_event_group * group;



int fuzz_single_setup()
{
  qid = queuename2id("LTERRC");
  group = eventname2addr("LTE_RRC_");

  return 1;
}

void fuzz_single()
{
    uint32_t input_size;
    uint16_t size;
    uart_puts("[+] Allocating Qitem\n");
    struct qitem_lte_rrc * item = pal_MemAlloc(4, sizeof(struct qitem_lte_rrc), __FILE__, __LINE__);
    if (!item) {
      uart_puts("ALLOC FAILED");
      return;
    } 
    uart_puts("[+] Getting Work\n");
    char * buf = getWork(&input_size);
    size = (uint16_t) input_size;
    // if (buf[0] == 0x46 || buf[0] == 0x44 || buf[0] == 0x54){
    //   startWork(0, 0xffffffff);
    //   doneWork(0);
    //   return ;
    // }
    uart_puts("[+] Received n bytes: ");
    uart_dump_hex((uint8_t *)buf, size); // Print some for testing

    // Max size before size is forced reduced
    if (size > 0x1000) {
    startWork(0, 0xffffffff); // memory range to collect coverage
    doneWork(0);
    return;
    }

    // make nas message structure
    // 1. pack length 
    uint8_t header[8] = "\x27\xb3\xaa\xaa\xaa\xaa";
    int headerLen = 6;
    int sizelen;
    uint8_t size_byte[2];
    if (size + headerLen <= 0x127){
      sizelen = 1;
      size_byte[0] = size + headerLen;
    } else{
      sizelen = 2;
      size_byte[0] = 0x80 | (((size + headerLen) >> 8) & 0x7F);
      size_byte[1] = (size + headerLen) & 0xFF;
    }
    uint8_t buffer[input_size + 0x10];
    buffer[0] = 0x08;
    buffer[1] = 0;
    int idx = 1;
    for (int i=0;i<sizelen;i++){
      buffer[idx] = buffer[idx] | (size_byte[i] >> 5);
      idx += 1;
      buffer[idx] = (size_byte[i] & 0x1f) << 3;
    }

    for (int i=0;i<headerLen;i++){
      buffer[idx] = buffer[idx] | (header[i] >> 5);
      idx += 1;
      buffer[idx] = (header[i] & 0x1f) << 3;
    }

    for (int i=0;i<size;i++){
      buffer[idx] = buffer[idx] | (buf[i] >> 5);
      idx += 1;
      buffer[idx] = (buf[i] & 0x1f) << 3;
    }
    

    char * asn_pl = pal_MemAlloc(4, idx + 1, __FILE__, __LINE__);

    uart_puts("[+] Filling the qitem\n");
    item->header.msgGroup = 0;
    item->header.size = sizeof(struct qitem_lte_rrc) - sizeof(struct qitem_header);
    item->header.op = 0x003b;
    item->pdu_type = 1;
    item->pl_size = (idx + 1); //

    memcpy(asn_pl, buffer, idx + 1);
    item->asn_pl = asn_pl;


    uart_puts("[+] FIRE\n");
    startWork(0, 0xffffffff); // memory range to collect coverage
    pal_MsgSendTo(qid, item, 2);
    uart_puts("[+] Setting Event\n");
    uart_dump_hex((uint8_t *) group, 4);
    uart_dump_hex((uint8_t *) &pal_SmSetEvent, 4);
    pal_SmSetEvent(&group, 4);
    uart_puts("[+] Event set\n");
    doneWork(0);
    uart_puts("[+] WorkDone\n");
}
