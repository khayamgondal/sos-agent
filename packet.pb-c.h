/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

#ifndef PROTOBUF_C_packet_2eproto__INCLUDED
#define PROTOBUF_C_packet_2eproto__INCLUDED

#include <google/protobuf-c/protobuf-c.h>

PROTOBUF_C_BEGIN_DECLS


typedef struct _Packet Packet;


/* --- enums --- */


/* --- messages --- */

struct  _Packet
{
  ProtobufCMessage base;
  int32_t seq_num;
  char *payload;
};
#define PACKET__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&packet__descriptor) \
    , 0, NULL }


/* Packet methods */
void   packet__init
                     (Packet         *message);
size_t packet__get_packed_size
                     (const Packet   *message);
size_t packet__pack
                     (const Packet   *message,
                      uint8_t             *out);
size_t packet__pack_to_buffer
                     (const Packet   *message,
                      ProtobufCBuffer     *buffer);
Packet *
       packet__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   packet__free_unpacked
                     (Packet *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Packet_Closure)
                 (const Packet *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor packet__descriptor;

PROTOBUF_C_END_DECLS


#endif  /* PROTOBUF_packet_2eproto__INCLUDED */