// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: message_type.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "message_type.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::EnumDescriptor* MessageType_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_message_5ftype_2eproto() {
  protobuf_AddDesc_message_5ftype_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "message_type.proto");
  GOOGLE_CHECK(file != NULL);
  MessageType_descriptor_ = file->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_message_5ftype_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
}

}  // namespace

void protobuf_ShutdownFile_message_5ftype_2eproto() {
}

void protobuf_AddDesc_message_5ftype_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\022message_type.proto*8\n\013MessageType\022\027\n\023R"
    "PC_WORKGROUPS_LIST\020@\022\020\n\013RPC_UNKNOWN\020\200\010", 78);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "message_type.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_message_5ftype_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_message_5ftype_2eproto {
  StaticDescriptorInitializer_message_5ftype_2eproto() {
    protobuf_AddDesc_message_5ftype_2eproto();
  }
} static_descriptor_initializer_message_5ftype_2eproto_;
const ::google::protobuf::EnumDescriptor* MessageType_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MessageType_descriptor_;
}
bool MessageType_IsValid(int value) {
  switch(value) {
    case 64:
    case 1024:
      return true;
    default:
      return false;
  }
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
