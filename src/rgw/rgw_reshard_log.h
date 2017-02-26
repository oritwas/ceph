// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab

#ifndef RGW_RESHARD_LOG_H
#define RGW_RESHARD_LOG_H

class RGWRados;


struct rgw_reshard_info {
  string bucket_name;
  string old_instance_id;
  string new_instance_id;
  uint32_t old_num_shards;
  uint32_t new_num_shards;
  
  rgw_reshard_info() {}
  rgw_reshard_info(const string& _bucket_name, const string& _old_instance_id, const string& _new_instance_id,
		   uint32_t _old_num_shards, uint32_t _new_num_shards) :
    bucket_name(_bucket_name), old_instance_id(_old_instance_id), new_instance_id(_new_instance_id),
    old_num_shards(_old_num_shards), new_num_shards(_new_num_shards) {}

  void encode(bufferlist& bl) const {
    ENCODE_START(1, 1, bl);
    ::encode(bucket_name, bl);
    ::encode(old_instance_id, bl);
    ::encode(new_instance_id, bl);
    ::encode(old_num_shards, bl);
    ::encode(new_num_shards, bl);
    ENCODE_FINISH(bl);
  }

  void decode(bufferlist::iterator& bl) {
    DECODE_START(1, bl);
    ::decode(bucket_name, bl);
    ::decode(old_instance_id, bl);
    ::decode(new_instance_id, bl);
    ::decode(old_num_shards, bl);
    ::decode(new_num_shards, bl);
    DECODE_FINISH(bl);
  }

  void dump(Formatter *f) const;
};
WRITE_CLASS_ENCODER(rgw_reshard_info)

class RGWReshardLog {
  RGWRados* store;
  string reshard_pool;
  string lock_name;
public:
  RGWReshardLog(RGWRados* store);
  void prepare_entry(cls_log_entry& entry, const string& bucket_name, const string& old_instance_id,
		     const string& new_instance_id, uint32_t old_num_shards, uint32_t new_num_shards);
  int add(const string& oid, list<cls_log_entry>& entries,
	    librados::AioCompletion *completion, bool monotonic_inc = true);
  int add(const string& oid, const ceph::real_time& ut, const string& section, const string& key,
	    bufferlist& bl);
  int list(const string& oid, const ceph::real_time& start_time, const ceph::real_time& end_time,
	     int max_entries, list<cls_log_entry>& entries,
	     const string& marker, string *out_marker, bool *truncated);
  int info(const string& oid, cls_log_header *header);
  int info_async(librados::IoCtx& io_ctx, const string& oid, cls_log_header *header,
		   librados::AioCompletion *completion);
  int trim(const string& oid, const ceph::real_time& start_time, const ceph::real_time& end_time,
	     const string& from_marker, const string& to_marker,
	     librados::AioCompletion *completion = nullptr);
};

#endif
