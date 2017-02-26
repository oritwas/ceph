// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab

#include "rgw_rados.h"
#include "rgw_reshard_log.h"
#include "cls/lock/cls_lock_client.h"

#define dout_context g_ceph_context
#define dout_subsys ceph_subsys_rgw

RGWReshardLog::RGWReshardLog(RGWRados* _store):store(_store),lock_name("reshard_lock")
{
  reshard_pool = store->get_zone_params().reshard_pool.name;
}

void RGWReshardLog::prepare_entry(cls_log_entry& entry, const string& bucket_name,
				  const string& old_instance_id, const string& new_instance_id, uint32_t old_num_shards,
				  uint32_t new_num_shards)
{

  rgw_reshard_info info(bucket_name, old_instance_id, new_instance_id, old_num_shards, new_num_shards);
  bufferlist bl;
  ::encode(info, bl);
  store->time_log_prepare_entry(entry, real_clock::now(), "reshard", "", bl);

}

int RGWReshardLog::add(const string& oid, const real_time& ut, const string& section, const string& key,
		       bufferlist& bl)
{
  librados::IoCtx io_ctx;
  rados::cls::lock::Lock l(lock_name);

  int ret = store->time_log_add_init(reshard_pool, io_ctx);
  if (ret < 0) {
    return ret;
  }

  ret = l.lock_exclusive(&io_ctx, oid);
  if (ret == -EBUSY) { /* already locked by another gc processor */
    dout(0) << "RGWReshardLog::add failed to acquire lock on " << oid << dendl;
    return 0;
  }
  if (ret < 0)
    return ret;

  ret =  store->time_log_add(reshard_pool, oid, ut, section, key, bl);

  l.unlock(&io_ctx, oid);
  return ret;  
}

int RGWReshardLog::add(const string& oid, std::list<cls_log_entry>& entries, librados::AioCompletion *completion,
		       bool monotonic_inc)
{
  librados::IoCtx io_ctx;
  rados::cls::lock::Lock l(lock_name);
  
  int ret = store->time_log_add_init(reshard_pool, io_ctx);
  if (ret < 0) {
    return ret;
  }

  ret = l.lock_exclusive(&io_ctx, oid);
  if (ret == -EBUSY) {
    dout(0) << "RGWReshardLog::add failed to acquire lock on " << oid << dendl;
    return 0;
  }
  if (ret < 0) {
    return ret;
  }

  ret = store->time_log_add(reshard_pool, oid, entries, completion, monotonic_inc);

  l.unlock(&io_ctx, oid);
  return ret;  
}

int RGWReshardLog::list(const string& oid, const real_time& start_time, const real_time& end_time,
			int max_entries, std::list<cls_log_entry>& entries,
			const string& marker,
			string *out_marker,
			bool *truncated)
{
  librados::IoCtx io_ctx;
  rados::cls::lock::Lock l(lock_name);

  int ret = store->time_log_add_init(reshard_pool, io_ctx);
  if (ret < 0) {
    return ret;
  }

  ret = l.lock_exclusive(&io_ctx, oid);
  if (ret == -EBUSY) {
    dout(0) << "RGWReshardLog::add failed to acquire lock on " << oid << dendl;
    return 0;
  }
  if (ret < 0)
    return ret;

  ret =  store->time_log_list(reshard_pool, oid, start_time, end_time, max_entries, entries, marker, out_marker,
			      truncated);

  l.unlock(&io_ctx, oid);
  return ret;  
}

int RGWReshardLog::info(const string& oid, cls_log_header *header)
{
  librados::IoCtx io_ctx;
  rados::cls::lock::Lock l(lock_name);

  int ret = store->time_log_add_init(reshard_pool, io_ctx);
  if (ret < 0) {
    return ret;
  }

  ret = l.lock_exclusive(&io_ctx, oid);
  if (ret == -EBUSY) {
    dout(0) << "RGWReshardLog::add failed to acquire lock on " << oid << dendl;
    return 0;
  }
  if (ret < 0)
    return ret;
  ret = store->time_log_info(reshard_pool, oid, header);

  l.unlock(&io_ctx, oid);
  return ret;  
}

int RGWReshardLog::info_async(librados::IoCtx& io_ctx, const string& oid, cls_log_header *header,
			      librados::AioCompletion *completion)
{
  rados::cls::lock::Lock l(lock_name);

  int ret = store->time_log_add_init(reshard_pool, io_ctx);
  if (ret < 0) {
    return ret;
  }

  ret = l.lock_exclusive(&io_ctx, oid);
  if (ret == -EBUSY) {
    dout(0) << "RGWReshardLog::add failed to acquire lock on " << oid << dendl;
    return 0;
  }
  if (ret < 0)
    return ret;

  ret = store->time_log_info_async(reshard_pool, io_ctx, oid, header, completion);

  l.unlock(&io_ctx, oid);
  return ret;
}

int RGWReshardLog::trim(const string& oid, const real_time& start_time, const real_time& end_time,
			const string& from_marker, const string& to_marker,
			librados::AioCompletion *completion)
{
  librados::IoCtx io_ctx;
  rados::cls::lock::Lock l(lock_name);

  int ret = store->time_log_add_init(reshard_pool, io_ctx);
  if (ret < 0) {
    return ret;
  }

  ret = l.lock_exclusive(&io_ctx, oid);
  if (ret == -EBUSY) {
    dout(0) << "RGWReshardLog::add failed to acquire lock on " << oid << dendl;
    return 0;
  }
  if (ret < 0)
    return ret;

  ret =  store->time_log_trim(reshard_pool, oid, start_time, end_time, from_marker, to_marker, completion);

  l.unlock(&io_ctx, oid);
  return ret;  

}
