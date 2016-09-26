// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: query.proto

#ifndef PROTOBUF_query_2eproto__INCLUDED
#define PROTOBUF_query_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace dio {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_query_2eproto();
void protobuf_AssignDesc_query_2eproto();
void protobuf_ShutdownFile_query_2eproto();

class Query;
class Answer;

// ===================================================================

class Query : public ::google::protobuf::Message {
 public:
  Query();
  virtual ~Query();

  Query(const Query& from);

  inline Query& operator=(const Query& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Query& default_instance();

  void Swap(Query* other);

  // implements Message ----------------------------------------------

  Query* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Query& from);
  void MergeFrom(const Query& from);
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
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int64 questionid = 1;
  inline bool has_questionid() const;
  inline void clear_questionid();
  static const int kQuestionidFieldNumber = 1;
  inline ::google::protobuf::int64 questionid() const;
  inline void set_questionid(::google::protobuf::int64 value);

  // required string questioner = 2;
  inline bool has_questioner() const;
  inline void clear_questioner();
  static const int kQuestionerFieldNumber = 2;
  inline const ::std::string& questioner() const;
  inline void set_questioner(const ::std::string& value);
  inline void set_questioner(const char* value);
  inline void set_questioner(const char* value, size_t size);
  inline ::std::string* mutable_questioner();
  inline ::std::string* release_questioner();
  inline void set_allocated_questioner(::std::string* questioner);

  // required string question = 3;
  inline bool has_question() const;
  inline void clear_question();
  static const int kQuestionFieldNumber = 3;
  inline const ::std::string& question() const;
  inline void set_question(const ::std::string& value);
  inline void set_question(const char* value);
  inline void set_question(const char* value, size_t size);
  inline ::std::string* mutable_question();
  inline ::std::string* release_question();
  inline void set_allocated_question(::std::string* question);

  // @@protoc_insertion_point(class_scope:dio.Query)
 private:
  inline void set_has_questionid();
  inline void clear_has_questionid();
  inline void set_has_questioner();
  inline void clear_has_questioner();
  inline void set_has_question();
  inline void clear_has_question();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int64 questionid_;
  ::std::string* questioner_;
  ::std::string* question_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_query_2eproto();
  friend void protobuf_AssignDesc_query_2eproto();
  friend void protobuf_ShutdownFile_query_2eproto();

  void InitAsDefaultInstance();
  static Query* default_instance_;
};
// -------------------------------------------------------------------

class Answer : public ::google::protobuf::Message {
 public:
  Answer();
  virtual ~Answer();

  Answer(const Answer& from);

  inline Answer& operator=(const Answer& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Answer& default_instance();

  void Swap(Answer* other);

  // implements Message ----------------------------------------------

  Answer* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Answer& from);
  void MergeFrom(const Answer& from);
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
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int64 questionid = 1;
  inline bool has_questionid() const;
  inline void clear_questionid();
  static const int kQuestionidFieldNumber = 1;
  inline ::google::protobuf::int64 questionid() const;
  inline void set_questionid(::google::protobuf::int64 value);

  // required string questioner = 2;
  inline bool has_questioner() const;
  inline void clear_questioner();
  static const int kQuestionerFieldNumber = 2;
  inline const ::std::string& questioner() const;
  inline void set_questioner(const ::std::string& value);
  inline void set_questioner(const char* value);
  inline void set_questioner(const char* value, size_t size);
  inline ::std::string* mutable_questioner();
  inline ::std::string* release_questioner();
  inline void set_allocated_questioner(::std::string* questioner);

  // required string answerer = 3;
  inline bool has_answerer() const;
  inline void clear_answerer();
  static const int kAnswererFieldNumber = 3;
  inline const ::std::string& answerer() const;
  inline void set_answerer(const ::std::string& value);
  inline void set_answerer(const char* value);
  inline void set_answerer(const char* value, size_t size);
  inline ::std::string* mutable_answerer();
  inline ::std::string* release_answerer();
  inline void set_allocated_answerer(::std::string* answerer);

  // repeated string solution = 4;
  inline int solution_size() const;
  inline void clear_solution();
  static const int kSolutionFieldNumber = 4;
  inline const ::std::string& solution(int index) const;
  inline ::std::string* mutable_solution(int index);
  inline void set_solution(int index, const ::std::string& value);
  inline void set_solution(int index, const char* value);
  inline void set_solution(int index, const char* value, size_t size);
  inline ::std::string* add_solution();
  inline void add_solution(const ::std::string& value);
  inline void add_solution(const char* value);
  inline void add_solution(const char* value, size_t size);
  inline const ::google::protobuf::RepeatedPtrField< ::std::string>& solution() const;
  inline ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_solution();

  // @@protoc_insertion_point(class_scope:dio.Answer)
 private:
  inline void set_has_questionid();
  inline void clear_has_questionid();
  inline void set_has_questioner();
  inline void clear_has_questioner();
  inline void set_has_answerer();
  inline void clear_has_answerer();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int64 questionid_;
  ::std::string* questioner_;
  ::std::string* answerer_;
  ::google::protobuf::RepeatedPtrField< ::std::string> solution_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];

  friend void  protobuf_AddDesc_query_2eproto();
  friend void protobuf_AssignDesc_query_2eproto();
  friend void protobuf_ShutdownFile_query_2eproto();

  void InitAsDefaultInstance();
  static Answer* default_instance_;
};
// ===================================================================


// ===================================================================

// Query

// required int64 questionid = 1;
inline bool Query::has_questionid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Query::set_has_questionid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Query::clear_has_questionid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Query::clear_questionid() {
  questionid_ = GOOGLE_LONGLONG(0);
  clear_has_questionid();
}
inline ::google::protobuf::int64 Query::questionid() const {
  return questionid_;
}
inline void Query::set_questionid(::google::protobuf::int64 value) {
  set_has_questionid();
  questionid_ = value;
}

// required string questioner = 2;
inline bool Query::has_questioner() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Query::set_has_questioner() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Query::clear_has_questioner() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Query::clear_questioner() {
  if (questioner_ != &::google::protobuf::internal::kEmptyString) {
    questioner_->clear();
  }
  clear_has_questioner();
}
inline const ::std::string& Query::questioner() const {
  return *questioner_;
}
inline void Query::set_questioner(const ::std::string& value) {
  set_has_questioner();
  if (questioner_ == &::google::protobuf::internal::kEmptyString) {
    questioner_ = new ::std::string;
  }
  questioner_->assign(value);
}
inline void Query::set_questioner(const char* value) {
  set_has_questioner();
  if (questioner_ == &::google::protobuf::internal::kEmptyString) {
    questioner_ = new ::std::string;
  }
  questioner_->assign(value);
}
inline void Query::set_questioner(const char* value, size_t size) {
  set_has_questioner();
  if (questioner_ == &::google::protobuf::internal::kEmptyString) {
    questioner_ = new ::std::string;
  }
  questioner_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Query::mutable_questioner() {
  set_has_questioner();
  if (questioner_ == &::google::protobuf::internal::kEmptyString) {
    questioner_ = new ::std::string;
  }
  return questioner_;
}
inline ::std::string* Query::release_questioner() {
  clear_has_questioner();
  if (questioner_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = questioner_;
    questioner_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Query::set_allocated_questioner(::std::string* questioner) {
  if (questioner_ != &::google::protobuf::internal::kEmptyString) {
    delete questioner_;
  }
  if (questioner) {
    set_has_questioner();
    questioner_ = questioner;
  } else {
    clear_has_questioner();
    questioner_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required string question = 3;
inline bool Query::has_question() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Query::set_has_question() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Query::clear_has_question() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Query::clear_question() {
  if (question_ != &::google::protobuf::internal::kEmptyString) {
    question_->clear();
  }
  clear_has_question();
}
inline const ::std::string& Query::question() const {
  return *question_;
}
inline void Query::set_question(const ::std::string& value) {
  set_has_question();
  if (question_ == &::google::protobuf::internal::kEmptyString) {
    question_ = new ::std::string;
  }
  question_->assign(value);
}
inline void Query::set_question(const char* value) {
  set_has_question();
  if (question_ == &::google::protobuf::internal::kEmptyString) {
    question_ = new ::std::string;
  }
  question_->assign(value);
}
inline void Query::set_question(const char* value, size_t size) {
  set_has_question();
  if (question_ == &::google::protobuf::internal::kEmptyString) {
    question_ = new ::std::string;
  }
  question_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Query::mutable_question() {
  set_has_question();
  if (question_ == &::google::protobuf::internal::kEmptyString) {
    question_ = new ::std::string;
  }
  return question_;
}
inline ::std::string* Query::release_question() {
  clear_has_question();
  if (question_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = question_;
    question_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Query::set_allocated_question(::std::string* question) {
  if (question_ != &::google::protobuf::internal::kEmptyString) {
    delete question_;
  }
  if (question) {
    set_has_question();
    question_ = question;
  } else {
    clear_has_question();
    question_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// Answer

// required int64 questionid = 1;
inline bool Answer::has_questionid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Answer::set_has_questionid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Answer::clear_has_questionid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Answer::clear_questionid() {
  questionid_ = GOOGLE_LONGLONG(0);
  clear_has_questionid();
}
inline ::google::protobuf::int64 Answer::questionid() const {
  return questionid_;
}
inline void Answer::set_questionid(::google::protobuf::int64 value) {
  set_has_questionid();
  questionid_ = value;
}

// required string questioner = 2;
inline bool Answer::has_questioner() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Answer::set_has_questioner() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Answer::clear_has_questioner() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Answer::clear_questioner() {
  if (questioner_ != &::google::protobuf::internal::kEmptyString) {
    questioner_->clear();
  }
  clear_has_questioner();
}
inline const ::std::string& Answer::questioner() const {
  return *questioner_;
}
inline void Answer::set_questioner(const ::std::string& value) {
  set_has_questioner();
  if (questioner_ == &::google::protobuf::internal::kEmptyString) {
    questioner_ = new ::std::string;
  }
  questioner_->assign(value);
}
inline void Answer::set_questioner(const char* value) {
  set_has_questioner();
  if (questioner_ == &::google::protobuf::internal::kEmptyString) {
    questioner_ = new ::std::string;
  }
  questioner_->assign(value);
}
inline void Answer::set_questioner(const char* value, size_t size) {
  set_has_questioner();
  if (questioner_ == &::google::protobuf::internal::kEmptyString) {
    questioner_ = new ::std::string;
  }
  questioner_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Answer::mutable_questioner() {
  set_has_questioner();
  if (questioner_ == &::google::protobuf::internal::kEmptyString) {
    questioner_ = new ::std::string;
  }
  return questioner_;
}
inline ::std::string* Answer::release_questioner() {
  clear_has_questioner();
  if (questioner_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = questioner_;
    questioner_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Answer::set_allocated_questioner(::std::string* questioner) {
  if (questioner_ != &::google::protobuf::internal::kEmptyString) {
    delete questioner_;
  }
  if (questioner) {
    set_has_questioner();
    questioner_ = questioner;
  } else {
    clear_has_questioner();
    questioner_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required string answerer = 3;
inline bool Answer::has_answerer() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Answer::set_has_answerer() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Answer::clear_has_answerer() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Answer::clear_answerer() {
  if (answerer_ != &::google::protobuf::internal::kEmptyString) {
    answerer_->clear();
  }
  clear_has_answerer();
}
inline const ::std::string& Answer::answerer() const {
  return *answerer_;
}
inline void Answer::set_answerer(const ::std::string& value) {
  set_has_answerer();
  if (answerer_ == &::google::protobuf::internal::kEmptyString) {
    answerer_ = new ::std::string;
  }
  answerer_->assign(value);
}
inline void Answer::set_answerer(const char* value) {
  set_has_answerer();
  if (answerer_ == &::google::protobuf::internal::kEmptyString) {
    answerer_ = new ::std::string;
  }
  answerer_->assign(value);
}
inline void Answer::set_answerer(const char* value, size_t size) {
  set_has_answerer();
  if (answerer_ == &::google::protobuf::internal::kEmptyString) {
    answerer_ = new ::std::string;
  }
  answerer_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Answer::mutable_answerer() {
  set_has_answerer();
  if (answerer_ == &::google::protobuf::internal::kEmptyString) {
    answerer_ = new ::std::string;
  }
  return answerer_;
}
inline ::std::string* Answer::release_answerer() {
  clear_has_answerer();
  if (answerer_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = answerer_;
    answerer_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Answer::set_allocated_answerer(::std::string* answerer) {
  if (answerer_ != &::google::protobuf::internal::kEmptyString) {
    delete answerer_;
  }
  if (answerer) {
    set_has_answerer();
    answerer_ = answerer;
  } else {
    clear_has_answerer();
    answerer_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// repeated string solution = 4;
inline int Answer::solution_size() const {
  return solution_.size();
}
inline void Answer::clear_solution() {
  solution_.Clear();
}
inline const ::std::string& Answer::solution(int index) const {
  return solution_.Get(index);
}
inline ::std::string* Answer::mutable_solution(int index) {
  return solution_.Mutable(index);
}
inline void Answer::set_solution(int index, const ::std::string& value) {
  solution_.Mutable(index)->assign(value);
}
inline void Answer::set_solution(int index, const char* value) {
  solution_.Mutable(index)->assign(value);
}
inline void Answer::set_solution(int index, const char* value, size_t size) {
  solution_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Answer::add_solution() {
  return solution_.Add();
}
inline void Answer::add_solution(const ::std::string& value) {
  solution_.Add()->assign(value);
}
inline void Answer::add_solution(const char* value) {
  solution_.Add()->assign(value);
}
inline void Answer::add_solution(const char* value, size_t size) {
  solution_.Add()->assign(reinterpret_cast<const char*>(value), size);
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
Answer::solution() const {
  return solution_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
Answer::mutable_solution() {
  return &solution_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace dio

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_query_2eproto__INCLUDED