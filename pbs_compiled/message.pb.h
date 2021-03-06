// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: message.proto

#ifndef PROTOBUF_message_2eproto__INCLUDED
#define PROTOBUF_message_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
#include "message_type.pb.h"
#include "message_workgroup.pb.h"
// @@protoc_insertion_point(includes)

namespace rpc {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_message_2eproto();
void protobuf_AssignDesc_message_2eproto();
void protobuf_ShutdownFile_message_2eproto();

class Request;
class Response;

// ===================================================================

class Request : public ::google::protobuf::Message {
 public:
  Request();
  virtual ~Request();

  Request(const Request& from);

  inline Request& operator=(const Request& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Request& default_instance();

  void Swap(Request* other);

  // implements Message ----------------------------------------------

  inline Request* New() const { return New(NULL); }

  Request* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Request& from);
  void MergeFrom(const Request& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(Request* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional .MessageType message_type = 1;
  bool has_message_type() const;
  void clear_message_type();
  static const int kMessageTypeFieldNumber = 1;
  ::MessageType message_type() const;
  void set_message_type(::MessageType value);

  // optional .rpc.WorkGroupsListRequest workgroups_list = 64;
  bool has_workgroups_list() const;
  void clear_workgroups_list();
  static const int kWorkgroupsListFieldNumber = 64;
  const ::rpc::WorkGroupsListRequest& workgroups_list() const;
  ::rpc::WorkGroupsListRequest* mutable_workgroups_list();
  ::rpc::WorkGroupsListRequest* release_workgroups_list();
  void set_allocated_workgroups_list(::rpc::WorkGroupsListRequest* workgroups_list);

  // optional int64 service_type = 4096;
  bool has_service_type() const;
  void clear_service_type();
  static const int kServiceTypeFieldNumber = 4096;
  ::google::protobuf::int64 service_type() const;
  void set_service_type(::google::protobuf::int64 value);

  // optional bool is_debug = 4097;
  bool has_is_debug() const;
  void clear_is_debug();
  static const int kIsDebugFieldNumber = 4097;
  bool is_debug() const;
  void set_is_debug(bool value);

  // @@protoc_insertion_point(class_scope:rpc.Request)
 private:
  inline void set_has_message_type();
  inline void clear_has_message_type();
  inline void set_has_workgroups_list();
  inline void clear_has_workgroups_list();
  inline void set_has_service_type();
  inline void clear_has_service_type();
  inline void set_has_is_debug();
  inline void clear_has_is_debug();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::rpc::WorkGroupsListRequest* workgroups_list_;
  int message_type_;
  bool is_debug_;
  ::google::protobuf::int64 service_type_;
  friend void  protobuf_AddDesc_message_2eproto();
  friend void protobuf_AssignDesc_message_2eproto();
  friend void protobuf_ShutdownFile_message_2eproto();

  void InitAsDefaultInstance();
  static Request* default_instance_;
};
// -------------------------------------------------------------------

class Response : public ::google::protobuf::Message {
 public:
  Response();
  virtual ~Response();

  Response(const Response& from);

  inline Response& operator=(const Response& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Response& default_instance();

  void Swap(Response* other);

  // implements Message ----------------------------------------------

  inline Response* New() const { return New(NULL); }

  Response* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Response& from);
  void MergeFrom(const Response& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(Response* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional .MessageType message_type = 1;
  bool has_message_type() const;
  void clear_message_type();
  static const int kMessageTypeFieldNumber = 1;
  ::MessageType message_type() const;
  void set_message_type(::MessageType value);

  // optional .rpc.WorkGroupsListResponse workgroups_list = 64;
  bool has_workgroups_list() const;
  void clear_workgroups_list();
  static const int kWorkgroupsListFieldNumber = 64;
  const ::rpc::WorkGroupsListResponse& workgroups_list() const;
  ::rpc::WorkGroupsListResponse* mutable_workgroups_list();
  ::rpc::WorkGroupsListResponse* release_workgroups_list();
  void set_allocated_workgroups_list(::rpc::WorkGroupsListResponse* workgroups_list);

  // optional int32 error_code = 2048;
  bool has_error_code() const;
  void clear_error_code();
  static const int kErrorCodeFieldNumber = 2048;
  ::google::protobuf::int32 error_code() const;
  void set_error_code(::google::protobuf::int32 value);

  // repeated string error_message = 2049;
  int error_message_size() const;
  void clear_error_message();
  static const int kErrorMessageFieldNumber = 2049;
  const ::std::string& error_message(int index) const;
  ::std::string* mutable_error_message(int index);
  void set_error_message(int index, const ::std::string& value);
  void set_error_message(int index, const char* value);
  void set_error_message(int index, const char* value, size_t size);
  ::std::string* add_error_message();
  void add_error_message(const ::std::string& value);
  void add_error_message(const char* value);
  void add_error_message(const char* value, size_t size);
  const ::google::protobuf::RepeatedPtrField< ::std::string>& error_message() const;
  ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_error_message();

  // optional string request_id = 2050;
  bool has_request_id() const;
  void clear_request_id();
  static const int kRequestIdFieldNumber = 2050;
  const ::std::string& request_id() const;
  void set_request_id(const ::std::string& value);
  void set_request_id(const char* value);
  void set_request_id(const char* value, size_t size);
  ::std::string* mutable_request_id();
  ::std::string* release_request_id();
  void set_allocated_request_id(::std::string* request_id);

  // @@protoc_insertion_point(class_scope:rpc.Response)
 private:
  inline void set_has_message_type();
  inline void clear_has_message_type();
  inline void set_has_workgroups_list();
  inline void clear_has_workgroups_list();
  inline void set_has_error_code();
  inline void clear_has_error_code();
  inline void set_has_request_id();
  inline void clear_has_request_id();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::rpc::WorkGroupsListResponse* workgroups_list_;
  int message_type_;
  ::google::protobuf::int32 error_code_;
  ::google::protobuf::RepeatedPtrField< ::std::string> error_message_;
  ::google::protobuf::internal::ArenaStringPtr request_id_;
  friend void  protobuf_AddDesc_message_2eproto();
  friend void protobuf_AssignDesc_message_2eproto();
  friend void protobuf_ShutdownFile_message_2eproto();

  void InitAsDefaultInstance();
  static Response* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// Request

// optional .MessageType message_type = 1;
inline bool Request::has_message_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Request::set_has_message_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Request::clear_has_message_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Request::clear_message_type() {
  message_type_ = 64;
  clear_has_message_type();
}
inline ::MessageType Request::message_type() const {
  // @@protoc_insertion_point(field_get:rpc.Request.message_type)
  return static_cast< ::MessageType >(message_type_);
}
inline void Request::set_message_type(::MessageType value) {
  assert(::MessageType_IsValid(value));
  set_has_message_type();
  message_type_ = value;
  // @@protoc_insertion_point(field_set:rpc.Request.message_type)
}

// optional .rpc.WorkGroupsListRequest workgroups_list = 64;
inline bool Request::has_workgroups_list() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Request::set_has_workgroups_list() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Request::clear_has_workgroups_list() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Request::clear_workgroups_list() {
  if (workgroups_list_ != NULL) workgroups_list_->::rpc::WorkGroupsListRequest::Clear();
  clear_has_workgroups_list();
}
inline const ::rpc::WorkGroupsListRequest& Request::workgroups_list() const {
  // @@protoc_insertion_point(field_get:rpc.Request.workgroups_list)
  return workgroups_list_ != NULL ? *workgroups_list_ : *default_instance_->workgroups_list_;
}
inline ::rpc::WorkGroupsListRequest* Request::mutable_workgroups_list() {
  set_has_workgroups_list();
  if (workgroups_list_ == NULL) {
    workgroups_list_ = new ::rpc::WorkGroupsListRequest;
  }
  // @@protoc_insertion_point(field_mutable:rpc.Request.workgroups_list)
  return workgroups_list_;
}
inline ::rpc::WorkGroupsListRequest* Request::release_workgroups_list() {
  clear_has_workgroups_list();
  ::rpc::WorkGroupsListRequest* temp = workgroups_list_;
  workgroups_list_ = NULL;
  return temp;
}
inline void Request::set_allocated_workgroups_list(::rpc::WorkGroupsListRequest* workgroups_list) {
  delete workgroups_list_;
  workgroups_list_ = workgroups_list;
  if (workgroups_list) {
    set_has_workgroups_list();
  } else {
    clear_has_workgroups_list();
  }
  // @@protoc_insertion_point(field_set_allocated:rpc.Request.workgroups_list)
}

// optional int64 service_type = 4096;
inline bool Request::has_service_type() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Request::set_has_service_type() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Request::clear_has_service_type() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Request::clear_service_type() {
  service_type_ = GOOGLE_LONGLONG(0);
  clear_has_service_type();
}
inline ::google::protobuf::int64 Request::service_type() const {
  // @@protoc_insertion_point(field_get:rpc.Request.service_type)
  return service_type_;
}
inline void Request::set_service_type(::google::protobuf::int64 value) {
  set_has_service_type();
  service_type_ = value;
  // @@protoc_insertion_point(field_set:rpc.Request.service_type)
}

// optional bool is_debug = 4097;
inline bool Request::has_is_debug() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Request::set_has_is_debug() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Request::clear_has_is_debug() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Request::clear_is_debug() {
  is_debug_ = false;
  clear_has_is_debug();
}
inline bool Request::is_debug() const {
  // @@protoc_insertion_point(field_get:rpc.Request.is_debug)
  return is_debug_;
}
inline void Request::set_is_debug(bool value) {
  set_has_is_debug();
  is_debug_ = value;
  // @@protoc_insertion_point(field_set:rpc.Request.is_debug)
}

// -------------------------------------------------------------------

// Response

// optional .MessageType message_type = 1;
inline bool Response::has_message_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Response::set_has_message_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Response::clear_has_message_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Response::clear_message_type() {
  message_type_ = 64;
  clear_has_message_type();
}
inline ::MessageType Response::message_type() const {
  // @@protoc_insertion_point(field_get:rpc.Response.message_type)
  return static_cast< ::MessageType >(message_type_);
}
inline void Response::set_message_type(::MessageType value) {
  assert(::MessageType_IsValid(value));
  set_has_message_type();
  message_type_ = value;
  // @@protoc_insertion_point(field_set:rpc.Response.message_type)
}

// optional .rpc.WorkGroupsListResponse workgroups_list = 64;
inline bool Response::has_workgroups_list() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Response::set_has_workgroups_list() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Response::clear_has_workgroups_list() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Response::clear_workgroups_list() {
  if (workgroups_list_ != NULL) workgroups_list_->::rpc::WorkGroupsListResponse::Clear();
  clear_has_workgroups_list();
}
inline const ::rpc::WorkGroupsListResponse& Response::workgroups_list() const {
  // @@protoc_insertion_point(field_get:rpc.Response.workgroups_list)
  return workgroups_list_ != NULL ? *workgroups_list_ : *default_instance_->workgroups_list_;
}
inline ::rpc::WorkGroupsListResponse* Response::mutable_workgroups_list() {
  set_has_workgroups_list();
  if (workgroups_list_ == NULL) {
    workgroups_list_ = new ::rpc::WorkGroupsListResponse;
  }
  // @@protoc_insertion_point(field_mutable:rpc.Response.workgroups_list)
  return workgroups_list_;
}
inline ::rpc::WorkGroupsListResponse* Response::release_workgroups_list() {
  clear_has_workgroups_list();
  ::rpc::WorkGroupsListResponse* temp = workgroups_list_;
  workgroups_list_ = NULL;
  return temp;
}
inline void Response::set_allocated_workgroups_list(::rpc::WorkGroupsListResponse* workgroups_list) {
  delete workgroups_list_;
  workgroups_list_ = workgroups_list;
  if (workgroups_list) {
    set_has_workgroups_list();
  } else {
    clear_has_workgroups_list();
  }
  // @@protoc_insertion_point(field_set_allocated:rpc.Response.workgroups_list)
}

// optional int32 error_code = 2048;
inline bool Response::has_error_code() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Response::set_has_error_code() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Response::clear_has_error_code() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Response::clear_error_code() {
  error_code_ = 0;
  clear_has_error_code();
}
inline ::google::protobuf::int32 Response::error_code() const {
  // @@protoc_insertion_point(field_get:rpc.Response.error_code)
  return error_code_;
}
inline void Response::set_error_code(::google::protobuf::int32 value) {
  set_has_error_code();
  error_code_ = value;
  // @@protoc_insertion_point(field_set:rpc.Response.error_code)
}

// repeated string error_message = 2049;
inline int Response::error_message_size() const {
  return error_message_.size();
}
inline void Response::clear_error_message() {
  error_message_.Clear();
}
inline const ::std::string& Response::error_message(int index) const {
  // @@protoc_insertion_point(field_get:rpc.Response.error_message)
  return error_message_.Get(index);
}
inline ::std::string* Response::mutable_error_message(int index) {
  // @@protoc_insertion_point(field_mutable:rpc.Response.error_message)
  return error_message_.Mutable(index);
}
inline void Response::set_error_message(int index, const ::std::string& value) {
  // @@protoc_insertion_point(field_set:rpc.Response.error_message)
  error_message_.Mutable(index)->assign(value);
}
inline void Response::set_error_message(int index, const char* value) {
  error_message_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:rpc.Response.error_message)
}
inline void Response::set_error_message(int index, const char* value, size_t size) {
  error_message_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:rpc.Response.error_message)
}
inline ::std::string* Response::add_error_message() {
  return error_message_.Add();
}
inline void Response::add_error_message(const ::std::string& value) {
  error_message_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:rpc.Response.error_message)
}
inline void Response::add_error_message(const char* value) {
  error_message_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:rpc.Response.error_message)
}
inline void Response::add_error_message(const char* value, size_t size) {
  error_message_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:rpc.Response.error_message)
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
Response::error_message() const {
  // @@protoc_insertion_point(field_list:rpc.Response.error_message)
  return error_message_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
Response::mutable_error_message() {
  // @@protoc_insertion_point(field_mutable_list:rpc.Response.error_message)
  return &error_message_;
}

// optional string request_id = 2050;
inline bool Response::has_request_id() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Response::set_has_request_id() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Response::clear_has_request_id() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Response::clear_request_id() {
  request_id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_request_id();
}
inline const ::std::string& Response::request_id() const {
  // @@protoc_insertion_point(field_get:rpc.Response.request_id)
  return request_id_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Response::set_request_id(const ::std::string& value) {
  set_has_request_id();
  request_id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:rpc.Response.request_id)
}
inline void Response::set_request_id(const char* value) {
  set_has_request_id();
  request_id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:rpc.Response.request_id)
}
inline void Response::set_request_id(const char* value, size_t size) {
  set_has_request_id();
  request_id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:rpc.Response.request_id)
}
inline ::std::string* Response::mutable_request_id() {
  set_has_request_id();
  // @@protoc_insertion_point(field_mutable:rpc.Response.request_id)
  return request_id_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Response::release_request_id() {
  clear_has_request_id();
  return request_id_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Response::set_allocated_request_id(::std::string* request_id) {
  if (request_id != NULL) {
    set_has_request_id();
  } else {
    clear_has_request_id();
  }
  request_id_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), request_id);
  // @@protoc_insertion_point(field_set_allocated:rpc.Response.request_id)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace rpc

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_message_2eproto__INCLUDED
