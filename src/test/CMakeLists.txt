# test_timers
add_executable(test_timers
  TestTimers.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(test_timers global ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS})

# test_signal_handlers
add_executable(test_signal_handlers
  TestSignalHandlers.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(test_signal_handlers global ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS})

# test_msgr
add_executable(test_msgr
  testmsgr.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(test_msgr global ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS})

# test_crypt
add_executable(test_crypt
  testcrypto.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(test_crypt
  global
  ${CRYPTO_LIBS}
  m
  ${EXTRALIBS}
  ${BLKID_LIBRARIES}
  ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS}
  )

# test_rados
add_executable(test_rados 
  osd/TestRados.cc
  osd/TestOpStat.cc
  osd/Object.cc osd/RadosModel.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(test_rados
  librados
  global
  ${BLKID_LIBRARIES}
  ${CMAKE_DL_LIBS}
  ${EXTRALIBS}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS}
  )

# test_mutate
add_executable(test_mutate
  test_mutate.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(test_mutate global librados ${BLKID_LIBRARIES}
  ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS})

# test_rewrite_latency
add_executable(test_rewrite_latency
  test_rewrite_latency.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(test_rewrite_latency common
  ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS}
  ${CMAKE_THREAD_LIBS_INIT} ${CRYPTO_LIBS} m ${EXTRALIBS})

# streamtest
add_executable(streamtest
  streamtest.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(streamtest os global ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS})

# test_trans
add_executable(test_trans
  test_trans.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(test_trans os global ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS})

# test_keys
add_executable(test_keys
  testkeys.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(test_keys mon global ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS})

## dencoder
set(dencoder_srcs
  encoding/ceph_dencoder.cc
  ${CMAKE_SOURCE_DIR}/src/krbd.cc
  ${CMAKE_SOURCE_DIR}/src/common/secret.c
  ${CMAKE_SOURCE_DIR}/src/common/TextTable.cc
  )
if(${WITH_RADOSGW})
  list(APPEND dencoder_srcs
    ${CMAKE_SOURCE_DIR}/src/rgw/rgw_dencoder.cc
    ${CMAKE_SOURCE_DIR}/src/rgw/rgw_acl.cc
    ${CMAKE_SOURCE_DIR}/src/rgw/rgw_common.cc
    ${CMAKE_SOURCE_DIR}/src/rgw/rgw_env.cc
    ${CMAKE_SOURCE_DIR}/src/rgw/rgw_json_enc.cc
  )
endif(${WITH_RADOSGW})
add_executable(dencoder ${dencoder_srcs} $<TARGET_OBJECTS:heap_profiler_objs>)
if(${WITH_RADOSGW})
  set(DENCODER_EXTRALIBS
    rgw_a
    cls_rgw_client
    curl
    expat
    fcgi
    resolv
  )
endif(${WITH_RADOSGW})
target_link_libraries(dencoder
  librados
  librbd
  global
  osd
  mds
  mon
  osdc
  cls_lock_client
  cls_refcount_client
  cls_log_client
  cls_statelog_client
  cls_version_client
  cls_replica_log_client
  cls_kvs
  cls_user_client
  ${DENCODER_EXTRALIBS}
  blkid
  udev
  keyutils
  ${EXTRALIBS}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  )

# get_command_descriptions
add_executable(get_command_descriptions
  common/get_command_descriptions.cc
  ${CMAKE_SOURCE_DIR}/src/common/TextTable.cc
  $<TARGET_OBJECTS:os_mon_objs>
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(get_command_descriptions
  mon
  global
  leveldb
  ${EXTRALIBS}
  ${BLKID_LIBRARIES}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  )

## Benchmarks

# smalliobench
set(smalliobench_srcs
  bench/small_io_bench.cc
  bench/rados_backend.cc
  bench/detailed_stat_collector.cc
  bench/bencher.cc
  )
add_executable(smalliobench
  ${smalliobench_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(smalliobench librados boost_program_options global
  ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS})

# smalliobenchfs
set(smalliobenchfs_srcs
  bench/small_io_bench_fs.cc
  bench/testfilestore_backend.cc
  bench/detailed_stat_collector.cc
  bench/bencher.cc
  )
add_executable(smalliobenchfs
  ${smalliobenchfs_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(smalliobenchfs librados boost_program_options os global
  ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS})

# smalliobenchdumb
set(smalliobenchdumb_srcs
  bench/small_io_bench_dumb.cc
  bench/dumb_backend.cc
  bench/detailed_stat_collector.cc
  bench/bencher.cc
  )
add_executable(smalliobenchdumb
  ${smalliobenchdumb_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(smalliobenchdumb librados boost_program_options os global
  ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS})

# smalliobenchrbd
set(smalliobenchrbd_srcs
  bench/small_io_bench_rbd.cc
  bench/rbd_backend.cc
  bench/detailed_stat_collector.cc
  bench/bencher.cc
  ${CMAKE_SOURCE_DIR}/src/common/TextTable.cc
  ${CMAKE_SOURCE_DIR}/src/common/secret.c
)
add_executable(smalliobenchrbd
  ${smalliobenchrbd_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(smalliobenchrbd
  librbd
  librados
  os
  global
  boost_program_options
  blkid
  udev
  ${BLKID_LIBRARIES}
  ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS}
  keyutils
  )

# tpbench
set(tpbench_srcs
  bench/tp_bench.cc
  bench/detailed_stat_collector.cc)
add_executable(tpbench
  ${tpbench_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(tpbench librados boost_program_options os global
  ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS})

# omapbench
set(omapbench_srcs
  omap_bench.cc
  )
add_executable(omapbench
  ${omapbench_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(omapbench
  librados
  boost_program_options
  os
  global
  ${BLKID_LIBRARIES}
  ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS}
  )

# kvstorebench
set(kvstorebench_srcs
  kv_store_bench.cc
  ${CMAKE_SOURCE_DIR}/src/key_value_store/kv_flat_btree_async.cc
  )
add_executable(kvstorebench
  ${kvstorebench_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(kvstorebench librados global ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS})

## System tests

# systest
set(libsystest_srcs system/cross_process_sem.cc
  system/systest_runnable.cc
  system/systest_settings.cc
  system/st_rados_create_pool.cc
  system/st_rados_delete_pool.cc
  system/st_rados_list_objects.cc
  system/st_rados_watch.cc
  system/st_rados_notify.cc)
add_library(systest STATIC ${libsystest_srcs})

# test_rados_list_parallel
add_executable(test_rados_list_parallel
  system/rados_list_parallel.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(test_rados_list_parallel librados systest global pthread
  rt ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS})

# test_rados_open_pools_parallel
set(test_rados_open_pools_parallel_srcs system/rados_open_pools_parallel.cc)
add_executable(test_rados_open_pools_parallel
  ${test_rados_open_pools_parallel_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(test_rados_open_pools_parallel librados systest global
  pthread rt ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS})

# test_rados_delete_pools_parallel
set(test_rados_delete_pools_parallel_srcs
  system/rados_delete_pools_parallel.cc
  system/st_rados_create_pool.cc
  system/st_rados_delete_pool.cc
  system/st_rados_list_objects.cc

  )
add_executable(test_rados_delete_pools_parallel
  ${test_rados_delete_pools_parallel_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(test_rados_delete_pools_parallel librados systest global
  pthread rt ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS})

# test_rados_watch_notify
set(test_rados_watch_notify_srcs
  system/rados_watch_notify.cc
  system/st_rados_create_pool.cc
  system/st_rados_delete_pool.cc
  system/st_rados_delete_objs.cc
  system/st_rados_watch.cc
  system/st_rados_notify.cc
  )
add_executable(test_rados_watch_notify
  ${test_rados_watch_notify_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(test_rados_watch_notify librados systest global
  pthread rt ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS})

# bench_log
set(bench_log_srcs
  bench_log.cc
  )
add_executable(bench_log
  ${bench_log_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(bench_log global pthread rt ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS})

## Unit tests

set(UNITTEST_LIBS gmock_main gmock gtest ${PTHREAD_LIBS})
set(UNITTEST_CXX_FLAGS "-I${CMAKE_SOURCE_DIR}/src/gmock/include -I${CMAKE_BINARY_DIR}/src/gmock/include -I${CMAKE_SOURCE_DIR}/src/gmock/gtest/include -I${CMAKE_BINARY_DIR}/src/gmock/gtest/include -fno-strict-aliasing")
  
# unittest_encoding
set(unittest_encoding_srcs
  encoding.cc
  )
add_executable(unittest_encoding
  ${unittest_encoding_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_encoding cephfs librados pthread rt m
  ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_encoding
  PROPERTIES COMPILE_FLAGS ${UNITTEST_CXX_FLAGS})
add_test(unittest_encoding unittest_encoding)

# unittest_addrs
set(unittest_addrs_srcs
  test_addrs.cc
  )
add_executable(unittest_addrs
  ${unittest_addrs_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_addrs cephfs librados pthread rt m
  ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_addrs
  PROPERTIES COMPILE_FLAGS ${UNITTEST_CXX_FLAGS})
add_test(unittest_addrs unittest_addrs)

#unittest_blkdev
add_executable(unittest_blkdev
  common/test_blkdev.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_blkdev global
  ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_blkdev
  PROPERTIES COMPILE_FLAGS ${UNITTEST_CXX_FLAGS})
add_test(unittest_blkdev unittest_blkdev)

# unittest_bloom_filter
set(unittest_bloom_filter_srcs
  common/test_bloom_filter.cc
  )
add_executable(unittest_bloom_filter
  ${unittest_bloom_filter_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_bloom_filter global
  ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_bloom_filter
  PROPERTIES COMPILE_FLAGS ${UNITTEST_CXX_FLAGS})
add_test(unittest_bloom_filter unittest_bloom_filter)

# unittest_histogram
add_executable(unittest_histogram
  common/histogram.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_histogram global
  ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_histogram
  PROPERTIES COMPILE_FLAGS ${UNITTEST_CXX_FLAGS})
add_test(unittest_histogram unittest_histogram)

# unittest_prioritized_queue
add_executable(unittest_prioritized_queue
  common/test_prioritized_queue.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_prioritized_queue global
  ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_prioritized_queue
  PROPERTIES COMPILE_FLAGS ${UNITTEST_CXX_FLAGS})
add_test(unittest_prioritized_queue unittest_prioritized_queue)

# unittest_str_map
set(unittest_str_map_srcs
  common/test_str_map.cc
  )
add_executable(unittest_str_map
  ${unittest_str_map_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_str_map common global
  ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS} ${UNITTEST_LIBS} common)
set_target_properties(unittest_str_map
  PROPERTIES COMPILE_FLAGS ${UNITTEST_CXX_FLAGS})
add_test(unittest_str_map unittest_str_map)

# unittest_sharedptr_registry
set(unittest_sharedptr_registry_srcs
  common/test_sharedptr_registry.cc
  )
add_executable(unittest_sharedptr_registry
  ${unittest_sharedptr_registry_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_sharedptr_registry global
  ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_sharedptr_registry
  PROPERTIES COMPILE_FLAGS ${UNITTEST_CXX_FLAGS})
add_test(unittest_sharedptr_registry unittest_sharedptr_registry)

# unittest_shared_cache
add_executable(unittest_shared_cache
  common/test_shared_cache.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_shared_cache common global
  ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_shared_cache
  PROPERTIES COMPILE_FLAGS ${UNITTEST_CXX_FLAGS})
add_test(unittest_shared_cache unittest_shared_cache)

# unittest_sloppy_crc_map
set(unittest_sloppy_crc_map_srcs
  common/test_sloppy_crc_map.cc
  )
add_executable(unittest_sloppy_crc_map
  ${unittest_sloppy_crc_map_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_sloppy_crc_map global
  ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_sloppy_crc_map
  PROPERTIES COMPILE_FLAGS ${UNITTEST_CXX_FLAGS})
add_test(unittest_sloppy_crc_map unittest_sloppy_crc_map)

# unittest_util
set(unittest_util_srcs
  common/test_util.cc
  ${CMAKE_SOURCE_DIR}/src/common/util.cc
  )
add_executable(unittest_util
  ${unittest_util_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_util
  global
  ${BLKID_LIBRARIES}
  ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS}
  ${UNITTEST_LIBS}
  )
set_target_properties(unittest_util
  PROPERTIES COMPILE_FLAGS ${UNITTEST_CXX_FLAGS})
add_test(unittest_util unittest_util)

# unittest_crush_wrapper
add_executable(unittest_crush_wrapper
  crush/CrushWrapper.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_crush_wrapper common global
  ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_crush_wrapper
  PROPERTIES COMPILE_FLAGS ${UNITTEST_CXX_FLAGS})
add_test(unittest_crush_wrapper unittest_crush_wrapper)

# unittest_crush
add_executable(unittest_crush
  crush/crush.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_crush common global
  ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_crush
  PROPERTIES COMPILE_FLAGS ${UNITTEST_CXX_FLAGS})
add_test(unittest_crush unittest_crush)

# unittest_osdmap
set(unittest_osdmap_srcs osd/TestOSDMap.cc)
add_executable(unittest_osdmap
  ${unittest_osdmap_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_osdmap global ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS}
  ${UNITTEST_LIBS})
set_target_properties(unittest_osdmap PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_osdmap unittest_osdmap)

# unittest_workqueue
set(unittest_workqueue_srcs test_workqueue.cc)
add_executable(unittest_workqueue
  ${unittest_workqueue_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_workqueue global ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_workqueue PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_workqueue unittest_workqueue)

# unittest_striper
set(unittest_striper_srcs test_striper.cc)
add_executable(unittest_striper
  ${unittest_striper_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_striper global ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS} 
  ${UNITTEST_LIBS})
set_target_properties(unittest_striper PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_striper unittest_striper)

# unittest_prebufferedstreambuf
set(unittest_prebufferedstreambuf_srcs test_prebufferedstreambuf.cc)
add_executable(unittest_prebufferedstreambuf
  ${unittest_prebufferedstreambuf_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_prebufferedstreambuf global ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_prebufferedstreambuf PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_prebufferedstreambuf unittest_prebufferedstreambuf)

# unittest_str_list
set(unittest_str_list_srcs test_str_list.cc)
add_executable(unittest_str_list
  ${unittest_str_list_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_str_list global ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_str_list PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_str_list unittest_str_list)

# unittest_log
set(unittest_log_srcs ${CMAKE_SOURCE_DIR}/src/log/test.cc)
add_executable(unittest_log
  ${unittest_log_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_log global ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS}
  ${UNITTEST_LIBS})
set_target_properties(unittest_log PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_log unittest_log)

# unittest_throttle
set(unittest_throttle_srcs common/Throttle.cc)
add_executable(unittest_throttle
  ${unittest_throttle_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_throttle global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_throttle PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_throttle unittest_throttle)

# unittest_ceph_argparse
set(unittest_ceph_argparse_srcs ceph_argparse.cc)
add_executable(unittest_ceph_argparse
  ${unittest_ceph_argparse_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_ceph_argparse global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_ceph_argparse PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_ceph_argparse unittest_ceph_argparse)

# unittest_ceph_compatset
set(unittest_ceph_compatset_srcs ceph_compatset.cc)
add_executable(unittest_ceph_compatset
  ${unittest_ceph_compatset_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_ceph_compatset global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_ceph_compatset PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_ceph_compatset unittest_ceph_compatset)

# unittest_msd_types
add_executable(unittest_msd_types
  fs/mds_types.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_msd_types global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_msd_types PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_msd_types unittest_msd_types)

# unittest_osd_types
set(unittest_osd_types_srcs osd/types.cc)
add_executable(unittest_osd_types
  ${unittest_osd_types_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_osd_types global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_osd_types PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_osd_types unittest_osd_types)

# unittest_lru
add_executable(unittest_lru
  common/test_lru.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_lru global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_lru PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_lru unittest_lru)

# unittest_io_priority
add_executable(unittest_io_priority
  common/test_io_priority.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_io_priority global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_io_priority PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_io_priority unittest_io_priority)

# unittest_gather
set(unittest_gather_srcs gather.cc)
add_executable(unittest_gather
  ${unittest_gather_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_gather global ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS}
  ${UNITTEST_LIBS})
set_target_properties(unittest_gather PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_gather unittest_gather)

# signals
set(unittest_signals_srcs signals.cc)
add_executable(unittest_signals
  ${unittest_signals_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_signals global ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS} 
  ${UNITTEST_LIBS})
set_target_properties(unittest_signals PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_signals unittest_signals)

# unittest_bufferlist
set(unittest_bufferlist_srcs bufferlist.cc)
add_executable(unittest_bufferlist
  ${unittest_bufferlist_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_bufferlist global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_bufferlist PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_bufferlist unittest_bufferlist)

# unittest_xlist
add_executable(unittest_xlist
  test_xlist.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_xlist global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_xlist PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_xlist unittest_xlist)

# unittest_crc32
set(unittest_crc32_srcs common/test_crc32c.cc)
add_executable(unittest_crc32
  ${unittest_crc32_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_crc32 global ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS}
  ${UNITTEST_LIBS})
set_target_properties(unittest_crc32 PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_crc32 unittest_crc32)

# unittest_arch
set(unittest_arch_srcs test_arch.cc)
add_executable(unittest_arch
  ${unittest_arch_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_arch global ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS}
  ${UNITTEST_LIBS})
set_target_properties(unittest_arch PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_arch unittest_arch)

# unittest_crypto
add_executable(unittest_crypto
  crypto.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_crypto global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_crypto PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_crypto unittest_crypto)

# unittest_crypto_init
set(unittest_crypto_init_srcs crypto_init.cc)
add_executable(unittest_crypto_init
  ${unittest_crypto_init_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_crypto_init global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_crypto_init PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_crypto_init unittest_crypto_init)

# unittest_perf_counters
set(unittest_perf_counters_srcs perf_counters.cc)
add_executable(unittest_perf_counters
  ${unittest_perf_counters_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_perf_counters global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_perf_counters PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_perf_counters unittest_perf_counters)

# unittest_admin_socket
set(unittest_admin_socket_srcs admin_socket.cc)
add_executable(unittest_admin_socket
  ${unittest_admin_socket_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_admin_socket global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_admin_socket PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_admin_socket unittest_admin_socket)

# unittest_ceph_crypto
set(unittest_ceph_crypto_srcs ceph_crypto.cc)
add_executable(unittest_ceph_crypto
  ${unittest_ceph_crypto_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_ceph_crypto global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_ceph_crypto PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_ceph_crypto unittest_ceph_crypto)

# unittest_utf8
set(unittest_utf8_srcs utf8.cc)
add_executable(unittest_utf8
  ${unittest_utf8_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_utf8 global ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS}
  ${UNITTEST_LIBS})
set_target_properties(unittest_utf8 PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_utf8 unittest_utf8)

# unittest_mime
set(unittest_mime_srcs mime.cc)
add_executable(unittest_mime
  ${unittest_mime_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_mime global ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS}
  ${UNITTEST_LIBS})
set_target_properties(unittest_mime PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_mime unittest_mime)

# unittest_escape
set(unittest_escape_srcs escape.cc)
add_executable(unittest_escape
  ${unittest_escape_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_escape global ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS}
  ${UNITTEST_LIBS})
set_target_properties(unittest_escape PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_escape unittest_escape)

# unittest_strtol
set(unittest_strtol_srcs strtol.cc)
add_executable(unittest_strtol
  ${unittest_strtol_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_strtol global ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS}
  ${UNITTEST_LIBS})
set_target_properties(unittest_strtol PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_strtol unittest_strtol)

# unittest_confutils
set(unittest_confutils_srcs confutils.cc)
add_executable(unittest_confutils
  ${unittest_confutils_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_confutils global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_confutils PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_confutils unittest_confutils)

# unittest_config
set(unittest_config_srcs common/test_config.cc)
add_executable(unittest_config
  ${unittest_config_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_config global ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS}
  ${UNITTEST_LIBS})
set_target_properties(unittest_config PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_config unittest_config)

# unittest_context
set(unittest_context_srcs common/test_context.cc)
add_executable(unittest_context
  ${unittest_context_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_context global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_context PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_context unittest_context)

# unittest_safe_io
add_executable(unittest_safe_io
  common/test_safe_io.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_safe_io global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_safe_io PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_safe_io unittest_safe_io)

# unittest_heartbeatmap
set(unittest_heartbeatmap_srcs heartbeat_map.cc)
add_executable(unittest_heartbeatmap
  ${unittest_heartbeatmap_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_heartbeatmap global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_heartbeatmap PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_heartbeatmap unittest_heartbeatmap)

if(${WITH_RADOSGW})
  # unittest_formatter
  set(unittest_formatter_srcs formatter.cc
    ${CMAKE_SOURCE_DIR}/src/rgw/rgw_formats.cc)
  add_executable(unittest_formatter
    ${unittest_formatter_srcs}
    $<TARGET_OBJECTS:heap_profiler_objs>
  )
  target_link_libraries(unittest_formatter global ${CMAKE_DL_LIBS}
    ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
  set_target_properties(unittest_formatter PROPERTIES COMPILE_FLAGS
    ${UNITTEST_CXX_FLAGS})
  add_test(unittest_formatter unittest_formatter)
endif(${WITH_RADOSGW})

# unittest_daemon_config
set(unittest_daemon_config_srcs daemon_config.cc)
add_executable(unittest_daemon_config
  ${unittest_daemon_config_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_daemon_config
  common
  global
  ${UNITTEST_LIBS}
  ${BLKID_LIBRARIES}
  ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS}
  ${EXTRALIBS}
  )
set_target_properties(unittest_daemon_config PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_daemon_confi unittest_daemon_config)

# unittest_ipaddr
add_executable(unittest_ipaddr test_ipaddr.cc)
target_link_libraries(unittest_ipaddr mon global ${CMAKE_DL_LIBS} 
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_ipaddr PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_ipaddr unittest_ipaddr)

# unittest_texttable
set(unittest_texttable_srcs
  test_texttable.cc
  ${CMAKE_SOURCE_DIR}/src/common/TextTable.cc
  )
add_executable(unittest_texttable
  ${unittest_texttable_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_texttable mon global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_texttable PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_texttable unittest_texttable)

# unittest_on_exit
set(unittest_on_exit_srcs on_exit.cc)
add_executable(unittest_on_exit
  ${unittest_on_exit_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_on_exit
  global
  ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS}
  ${UNITTEST_LIBS})
set_target_properties(unittest_on_exit PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_on_exit unittest_on_exit)

# unittest_readahead
set(unittest_readahead_srcs common/Readahead.cc)
add_executable(unittest_readahead
  ${unittest_readahead_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_readahead global
  ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_readahead PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_readahead unittest_readahead)


# unittest_tableformatter
set(unittest_readahead_srcs common/test_tableformatter.cc)
add_executable(unittest_tableformatter
  ${unittest_tableformatter_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_tableformatter global
  ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_tableformatter PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_tableformatter unittest_tableformatter)

# unittest_bit_vector
set(unittest_bit_vector_srcs common/test_bit_vector.cc)
add_executable(unittest_bit_vector
  ${unittest_bit_vector_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_bit_vector global
  ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_bit_vector PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_bit_vector unittest_bit_vector)

# unittest_subprocess
set(unittest_subprocess_srcs test_subprocess.cc)
add_executable(unittest_subprocess
  ${unittest_subprocess_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_subprocess
  global
  ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS}
  ${UNITTEST_LIBS})
set_target_properties(unittest_subprocess PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_subprocess unittest_subprocess)

if(${WITH_RADOSGW})
  # test_cors
  set(test_cors_srcs test_cors.cc)
  add_executable(test_cors
    ${test_cors_srcs}
    $<TARGET_OBJECTS:heap_profiler_objs>
    )
  target_link_libraries(test_cors
    librados
    rgw_a
    global
    curl
    uuid
    expat
    ${BLKID_LIBRARIES}
    ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
  set_target_properties(test_cors PROPERTIES COMPILE_FLAGS
    ${UNITTEST_CXX_FLAGS})
  add_test(test_cors test_cors)
  
  # test_rgw_manifest
  set(test_rgw_manifest_srcs rgw/test_rgw_manifest.cc)
  add_executable(test_rgw_manifest
    ${test_rgw_manifest_srcs}
    $<TARGET_OBJECTS:heap_profiler_objs>
    )
  target_link_libraries(test_rgw_manifest
    rgw_a
    cls_rgw_client
    cls_lock_client
    cls_refcount_client
    cls_log_client
    cls_statelog_client
    cls_version_client
    cls_replica_log_client
    cls_kvs
    cls_user_client
    librados
    global
    curl
    uuid
    expat
    ${BLKID_LIBRARIES}
    ${CMAKE_DL_LIBS}
    ${TCMALLOC_LIBS}
    ${UNITTEST_LIBS}
    ${CRYPTO_LIBS}
    )
  set_target_properties(test_rgw_manifest PROPERTIES COMPILE_FLAGS
    ${UNITTEST_CXX_FLAGS})
  add_test(test_rgw_manifest test_rgw_manifest)
  # test_cls_rgw_meta
  set(test_cls_rgw_meta_srcs test_rgw_admin_meta.cc)
  add_executable(test_cls_rgw_meta
    ${test_cls_rgw_meta_srcs}
    $<TARGET_OBJECTS:heap_profiler_objs>
    )
  target_link_libraries(test_cls_rgw_meta
    librados
    rgw_a
    global
    curl
    uuid
    expat
    cls_version_client
    cls_log_client
    cls_statelog_client
    cls_refcount_client
    cls_rgw_client
    cls_user_client
    cls_lock_client
    boost_regex
    ${BLKID_LIBRARIES}
    ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS} ${UNITTEST_LIBS} ${CRYPTO_LIBS})
  set_target_properties(test_cls_rgw_meta PROPERTIES COMPILE_FLAGS
    ${UNITTEST_CXX_FLAGS})
  add_test(test_cls_rgw_meta test_cls_rgw_meta)
  # test_cls_rgw_log
  set(test_cls_rgw_log_srcs
    test_rgw_admin_log.cc
    )
  add_executable(test_cls_rgw_log
    ${test_cls_rgw_log_srcs}
    $<TARGET_OBJECTS:heap_profiler_objs>
    )
  target_link_libraries(test_cls_rgw_log
    librados
    rgw_a
    global
    curl
    uuid
    expat
    cls_version_client
    cls_log_client
    cls_statelog_client
    cls_refcount_client
    cls_rgw_client
    cls_user_client
    cls_lock_client
    boost_regex
    ${BLKID_LIBRARIES}
    ${CMAKE_DL_LIBS}
    ${TCMALLOC_LIBS}
    ${UNITTEST_LIBS}
    ${EXTRALIBS}
    ${CRYPTO_LIBS}
    )
  set_target_properties(test_cls_rgw_log PROPERTIES COMPILE_FLAGS
    ${UNITTEST_CXX_FLAGS})
  add_test(test_cls_rgw_log test_cls_rgw_log)
  
  # test_cls_rgw_opstate
  set(test_cls_rgw_opstate_srcs test_rgw_admin_opstate.cc)
  add_executable(test_cls_rgw_opstate
    ${test_cls_rgw_opstate_srcs}
    $<TARGET_OBJECTS:heap_profiler_objs>
    )
  target_link_libraries(test_cls_rgw_opstate
    rgw_a
    librados
    cls_version_client
    cls_log_client
    cls_statelog_client
    cls_refcount_client
    cls_rgw_client
    cls_user_client
    cls_lock_client
    global
    curl
    uuid
    expat
    ${BLKID_LIBRARIES}
    ${CMAKE_DL_LIBS}
    ${TCMALLOC_LIBS}
    ${UNITTEST_LIBS}
    ${CRYPTO_LIBS}
    ${EXTRALIBS}
    )
  set_target_properties(test_cls_rgw_opstate PROPERTIES COMPILE_FLAGS
    ${UNITTEST_CXX_FLAGS})
  add_test(test_cls_rgw_opstate test_cls_rgw_opstate)
endif(${WITH_RADOSGW})

# radostest 
set(libradostest_srcs librados/test.cc librados/TestCase.cc)
add_library(radostest STATIC ${libradostest_srcs})
set_target_properties(radostest PROPERTIES COMPILE_FLAGS ${UNITTEST_CXX_FLAGS})

# multi_stress_watch
add_executable(multi_stress_watch
  multi_stress_watch.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(multi_stress_watch librados global radostest
  ${BLKID_LIBRARIES} ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS})

add_executable(test_librbd
  librbd/test_librbd.cc
  librbd/test_fixture.cc
  librbd/test_ImageWatcher.cc
  librbd/test_internal.cc
  librbd/test_support.cc
  librbd/test_main.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  ${CMAKE_SOURCE_DIR}/src/common/TextTable.cc
  ${CMAKE_SOURCE_DIR}/src/common/secret.c
  )
set_target_properties(test_librbd PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_librbd
  librbd
  librados
  ${UNITTEST_LIBS}
  global
  ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS}
  ${CRYPTO_LIBS}
  ${EXTRALIBS}
  blkid
  udev
  keyutils
  radostest
  )

add_executable(test_librbd_fsx
  librbd/fsx.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  ${CMAKE_SOURCE_DIR}/src/common/TextTable.cc
  ${CMAKE_SOURCE_DIR}/src/common/secret.c
  )
target_link_libraries(test_librbd_fsx
  librbd
  librados
  global
  m
  ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS}
  ${CRYPTO_LIBS}
  ${EXTRALIBS}
  blkid
  udev
  keyutils
  )

add_executable(test_cls_rbd
  cls_rbd/test_cls_rbd.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  ${CMAKE_SOURCE_DIR}/src/common/TextTable.cc
  ${CMAKE_SOURCE_DIR}/src/common/secret.c
  )
set_target_properties(test_cls_rbd PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_cls_rbd
  librbd
  cls_rbd
  cls_lock
  librados
  global
  ${UNITTEST_LIBS}
  ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS}
  ${CRYPTO_LIBS}
  ${EXTRALIBS}
  radostest
  blkid
  udev
  keyutils
  )

add_executable(test_cls_refcount
  cls_refcount/test_cls_refcount.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_cls_refcount PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_cls_refcount
  librados
  cls_refcount_client
  global
  ${UNITTEST_LIBS}
  ${BLKID_LIBRARIES}
  ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS}
  ${CRYPTO_LIBS}
  ${EXTRALIBS}
  radostest
  )

add_executable(test_cls_version
  cls_version/test_cls_version.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_cls_version PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_cls_version
  librados
  cls_version_client
  global
  ${UNITTEST_LIBS}
  ${BLKID_LIBRARIES}
  ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS}
  ${CRYPTO_LIBS}
  ${EXTRALIBS}
  radostest
  )

add_executable(test_cls_log
  cls_log/test_cls_log.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_cls_log PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_cls_log
  librados
  cls_log_client
  global
  radostest
  ${UNITTEST_LIBS}
  ${BLKID_LIBRARIES}
  ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS}
  ${CRYPTO_LIBS}
  ${EXTRALIBS}
  )

add_executable(test_cls_statelog
  cls_statelog/test_cls_statelog.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_cls_statelog PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_cls_statelog
  librados
  cls_statelog_client
  global
  ${UNITTEST_LIBS}
  ${BLKID_LIBRARIES}
  ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS}
  ${CRYPTO_LIBS}
  ${EXTRALIBS}
  radostest
  )

add_executable(test_cls_replica_log
  cls_replica_log/test_cls_replica_log.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_cls_replica_log PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_cls_replica_log
  librados
  cls_replica_log_client
  global
  ${UNITTEST_LIBS}
  ${BLKID_LIBRARIES}
  ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS}
  ${CRYPTO_LIBS}
  ${EXTRALIBS}
  radostest
  )

add_executable(test_cls_lock
  cls_lock/test_cls_lock.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_cls_lock PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_cls_lock
  cls_lock
  librados
  global
  ${UNITTEST_LIBS}
  ${BLKID_LIBRARIES}
  ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS}
  ${CRYPTO_LIBS}
  ${EXTRALIBS}
  radostest
  )

add_executable(test_cls_hello
  cls_hello/test_cls_hello.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_cls_hello PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_cls_hello
  librados
  global
  ${EXTRALIBS}
  ${BLKID_LIBRARIES}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  radostest
  ${UNITTEST_LIBS}
  )

if(${WITH_RADOSGW})
  add_executable(test_cls_rgw
    cls_rgw/test_cls_rgw.cc
    $<TARGET_OBJECTS:heap_profiler_objs>
    )
  set_target_properties(test_cls_rgw PROPERTIES COMPILE_FLAGS
    ${UNITTEST_CXX_FLAGS})
  target_link_libraries(test_cls_rgw
    cls_rgw_client
    librados
    global
    ${UNITTEST_LIBS}
    ${EXTRALIBS}
    ${BLKID_LIBRARIES}
    ${TCMALLOC_LIBS}
    ${CMAKE_DL_LIBS}
    radostest)
endif(${WITH_RADOSGW})

add_executable(test_mon_workloadgen
  mon/test_mon_workloadgen.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(test_mon_workloadgen
  os
  osdc
  global
  ${EXTRALIBS}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  )

add_executable(test_rados_api_cmd
  librados/cmd.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_rados_api_cmd PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_rados_api_cmd
  librados
  global
  ${UNITTEST_LIBS}
  ${EXTRALIBS}
  ${BLKID_LIBRARIES}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  radostest)

add_executable(test_rados_api_io
  librados/io.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_rados_api_io PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_rados_api_io
  librados
  global
  ${UNITTEST_LIBS}
  ${EXTRALIBS}
  ${BLKID_LIBRARIES}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  radostest
  )

add_executable(test_rados_api_c_write_operations
  librados/c_write_operations.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_rados_api_c_write_operations PROPERTIES
  COMPILE_FLAGS ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_rados_api_c_write_operations
  librados
  global
  ${UNITTEST_LIBS}
  ${EXTRALIBS}
  ${BLKID_LIBRARIES}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  radostest)

add_executable(test_rados_api_c_read_operations
  librados/c_read_operations.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_rados_api_c_read_operations PROPERTIES COMPILE_FLAGS 
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_rados_api_c_read_operations
  librados
  global
  ${UNITTEST_LIBS}
  ${EXTRALIBS}
  ${BLKID_LIBRARIES}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  radostest
  )

add_executable(test_rados_api_aio
  librados/aio.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_rados_api_aio PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_rados_api_aio
  librados
  global
  ${UNITTEST_LIBS}
  ${EXTRALIBS}
  ${BLKID_LIBRARIES}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  radostest
  )

add_executable(test_rados_api_list
  librados/list.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_rados_api_list PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_rados_api_list
  librados
  global
  ${UNITTEST_LIBS}
  ${EXTRALIBS}
  ${BLKID_LIBRARIES}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  radostest)

add_executable(test_rados_api_pool
  librados/pool.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_rados_api_pool PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS}
  )
target_link_libraries(test_rados_api_pool
  librados
  global
  ${UNITTEST_LIBS}
  ${EXTRALIBS}
  ${BLKID_LIBRARIES}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  radostest
  )

add_executable(test_rados_api_stat
  librados/stat.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_rados_api_stat PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_rados_api_stat
  librados
  global
  ${UNITTEST_LIBS}
  ${EXTRALIBS}
  ${BLKID_LIBRARIES}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  radostest
  )

add_executable(test_rados_api_watch_notify
  librados/watch_notify.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_rados_api_watch_notify PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_rados_api_watch_notify
  librados
  global
  ${UNITTEST_LIBS}
  ${EXTRALIBS}
  ${BLKID_LIBRARIES}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  radostest
  )

add_executable(test_rados_api_cls
  librados/cls.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_rados_api_cls PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_rados_api_cls
  librados
  global
  ${UNITTEST_LIBS}
  ${EXTRALIBS}
  ${BLKID_LIBRARIES}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  radostest
  )

add_executable(test_rados_api_misc
  librados/misc.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_rados_api_misc PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_rados_api_misc
  librados
  global
  ${UNITTEST_LIBS}
  ${EXTRALIBS}
  ${BLKID_LIBRARIES}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  radostest
  )

add_executable(test_rados_api_lock
  librados/lock.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_rados_api_lock PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_rados_api_lock
  librados
  global
  ${UNITTEST_LIBS}
  ${EXTRALIBS}
  ${BLKID_LIBRARIES}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  radostest
  )

if(${WITH_CEPHFS})
  add_executable(test_libcephfs
    libcephfs/test.cc
    libcephfs/readdir_r_cb.cc
    libcephfs/caps.cc
    libcephfs/multiclient.cc
    libcephfs/flock.cc
    $<TARGET_OBJECTS:heap_profiler_objs>
  )
  set_target_properties(test_libcephfs PROPERTIES COMPILE_FLAGS
    ${UNITTEST_CXX_FLAGS})
  target_link_libraries(test_libcephfs
    libcephfs
    ${UNITTEST_LIBS}
    ${EXTRALIBS}
    ${TCMALLOC_LIBS}
    ${CMAKE_DL_LIBS}
    )
endif(${WITH_CEPHFS})  

add_executable(test_objectstore
  objectstore/store_test.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_objectstore PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_objectstore
  os
  common
  ${UNITTEST_LIBS}
  global
  ${EXTRALIBS}
  ${BLKID_LIBRARIES}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  )

add_executable(test_objectstore_workloadgen
  objectstore/workload_generator.cc
  objectstore/TestObjectStoreState.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(test_objectstore_workloadgen
  os
  global
  ${EXTRALIBS}
  ${BLKID_LIBRARIES}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  )

add_executable(test_filestore_idempotent
  objectstore/test_idempotent.cc
  objectstore/FileStoreTracker.cc
  common/ObjectContents.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(test_filestore_idempotent
  os
  global
  ${EXTRALIBS}
  ${BLKID_LIBRARIES}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  )

add_executable(test_filestore_idempotent_sequence
  objectstore/test_idempotent_sequence.cc
  objectstore/DeterministicOpSequence.cc
  objectstore/TestObjectStoreState.cc
  objectstore/FileStoreDiff.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(test_filestore_idempotent_sequence
  os
  global
  ${EXTRALIBS}
  ${BLKID_LIBRARIES}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  )

add_executable(test_xattr_bench
  xattr_bench.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_xattr_bench PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_xattr_bench
  os
  common
  ${UNITTEST_LIBS}
  global
  ${EXTRALIBS}
  ${BLKID_LIBRARIES}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  )

add_executable(test_filejournal
  test_filejournal.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_filejournal PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_filejournal
  os
  common
  ${UNITTEST_LIBS}
  global
  ${EXTRALIBS}
  ${BLKID_LIBRARIES}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  ${EXTRALIBS}
  )

add_executable(test_stress_watch
  test_stress_watch.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_stress_watch PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_stress_watch
  librados
  global
  ${UNITTEST_LIBS}
  radostest
  ${EXTRALIBS}
  ${BLKID_LIBRARIES}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  )

add_executable(test_objectcacher_stress
  osdc/object_cacher_stress.cc
  osdc/FakeWriteback.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(test_objectcacher_stress
  osdc
  global
  ${EXTRALIBS}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  )

add_executable(test_object_map
  ObjectMap/test_object_map.cc
  ObjectMap/KeyValueDBMemory.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_object_map PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_object_map
  os
  common
  ${UNITTEST_LIBS}
  global
  ${EXTRALIBS}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  )

add_executable(test_keyvaluedb_atomicity
  ObjectMap/test_keyvaluedb_atomicity.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_keyvaluedb_atomicity PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_keyvaluedb_atomicity
  os
  common
  ${UNITTEST_LIBS}
  global
  ${EXTRALIBS}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  )

add_executable(test_keyvaluedb_iterators
  ObjectMap/test_keyvaluedb_iterators.cc
  ObjectMap/KeyValueDBMemory.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(test_keyvaluedb_iterators PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(test_keyvaluedb_iterators
  os
  common
  ${UNITTEST_LIBS}
  global
  ${EXTRALIBS}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  )

if(${WITH_FUSE})
  add_executable(test_cfuse_cache_invalidate
    test_cfuse_cache_invalidate.cc
    )
  target_link_libraries(test_cfuse_cache_invalidate
    global
    os
    ${EXTRALIBS}
    ${TCMALLOC_LIBS}
    ${CMAKE_DL_LIBS}
    )
endif(${WITH_FUSE})

if(${WITH_CEPHFS})
  add_executable(test_c_headers
    test_c_headers.c
    $<TARGET_OBJECTS:heap_profiler_objs>
  )
  target_link_libraries(test_c_headers
    librados
    rados
    libcephfs
    ${EXTRALIBS}
    ${TCMALLOC_LIBS}
    ${CMAKE_DL_LIBS}
    )
endif(${WITH_CEPHFS})

add_executable(test_get_blkdev_size
  test_get_blkdev_size.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(test_get_blkdev_size
  common
  pthread
  ${EXTRALIBS}
  ${BLKID_LIBRARIES}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  )

add_executable(simple_server
  messenger/simple_server.cc
  messenger/simple_dispatcher.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(simple_server
  os global common boost_regex
  ${EXTRALIBS}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  )

add_executable(simple_client
  messenger/simple_client.cc
  messenger/simple_dispatcher.cc
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(simple_client
  os global common boost_regex
  ${EXTRALIBS}
  ${TCMALLOC_LIBS}
  ${CMAKE_DL_LIBS}
  )

if(HAVE_XIO)
  add_executable(xio_server
    messenger/xio_server.cc
    messenger/xio_dispatcher.cc
    $<TARGET_OBJECTS:heap_profiler_objs>
    )
  target_link_libraries(xio_server
    os global common boost_regex
    ${Xio_LIBRARY} ibverbs rdmacm pthread rt
    ${EXTRALIBS}
    ${TCMALLOC_LIBS}
    ${CMAKE_DL_LIBS}
    )

  add_executable(xio_client
    messenger/xio_client.cc
    messenger/xio_dispatcher.cc
    $<TARGET_OBJECTS:heap_profiler_objs>
    )
  target_link_libraries(xio_client
    os global common boost_regex
    ${Xio_LIBRARY} ibverbs rdmacm pthread rt
    ${EXTRALIBS}
    ${TCMALLOC_LIBS}
    ${CMAKE_DL_LIBS}
    )
endif(HAVE_XIO)

# client unittests

# unittest_librados
set(unittest_librados_srcs librados/librados.cc)
add_executable(unittest_librados
  ${unittest_librados_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_librados
  librados
  global
  ${BLKID_LIBRARIES}
  ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS}
  ${UNITTEST_LIBS}
  )
set_target_properties(unittest_librados PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_librados unittest_librados)

# unittest_librados_config
set(unittest_librados_config_srcs librados/librados_config.cc)
add_executable(unittest_librados_config
  ${unittest_librados_config_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_librados_config
  librados
  global
  ${BLKID_LIBRARIES}
  ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS}
  ${UNITTEST_LIBS}
  )
set_target_properties(unittest_librados_config PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_librados_config unittest_librados_config)

if(${WITH_RBD})
  # unittest_rbd_replay
  set(unittest_rbd_replay_srcs
    test_rbd_replay.cc
    ${CMAKE_SOURCE_DIR}/src/common/secret.c)
  add_executable(unittest_rbd_replay
    ${unittest_rbd_replay_srcs}
    $<TARGET_OBJECTS:heap_profiler_objs>
    )
  target_link_libraries(unittest_rbd_replay
    librbd
    librados
    global
    udev
    keyutils
    librbd_replay
    ${BLKID_LIBRARIES}
    ${CMAKE_DL_LIBS}
    ${TCMALLOC_LIBS}
    ${UNITTEST_LIBS}
    )
  set_target_properties(unittest_rbd_replay PROPERTIES COMPILE_FLAGS
    ${UNITTEST_CXX_FLAGS})
  add_test(unittest_rbd_replay unittest_rbd_replay)
endif(${WITH_RBD})

# unittest_base64
set(unittest_base64_srcs base64.cc)
add_executable(unittest_base64
  ${unittest_base64_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_base64 global ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_base64 PROPERTIES COMPILE_FLAGS ${UNITTEST_CXX_FLAGS})

# run_cmd
set(unittest_run_cmd_srcs run_cmd.cc)
add_executable(unittest_run_cmd
  ${unittest_run_cmd_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_run_cmd global ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS} 
  ${UNITTEST_LIBS})
set_target_properties(unittest_run_cmd PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})

# unittest_simple_spin
set(unittest_simple_spin_srcs simple_spin.cc)
add_executable(unittest_simple_spin
  ${unittest_simple_spin_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_simple_spin global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_simple_spin PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})

# unittest_libcephfs_config
set(unittest_libcephfs_config_srcs libcephfs_config.cc)
add_executable(unittest_libcephfs_config
  ${unittest_libcephfs_config_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_libcephfs_config cephfs ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_libcephfs_config PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_libcephfs_config unittest_libcephfs_config)

# unittest_lfnindex
set(unittest_lfnindex_srcs os/TestLFNIndex.cc)
add_executable(unittest_lfnindex
  ${unittest_lfnindex_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_lfnindex os global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_lfnindex PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})

# unittest_mon_moncap
set(unittest_mon_moncap_srcs mon/moncap.cc)
add_executable(unittest_mon_moncap
  ${unittest_mon_moncap_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_mon_moncap mon global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_mon_moncap PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_mon_moncap unittest_mon_moncap)

# unittest_mon_pgmap
set(unittest_mon_pgmap_srcs mon/PGMap.cc)
add_executable(unittest_mon_pgmap
  ${unittest_mon_pgmap_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_mon_pgmap mon global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_mon_pgmap PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_mon_pgmap unittest_mon_pgmap)

# unittest_ecbackend
set(unittest_ecbackend_srcs osd/TestECBackend.cc)
add_executable(unittest_ecbackend
  ${unittest_ecbackend_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_ecbackend osd global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_ecbackend PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_ecbackend unittest_ecbackend)

# unittest_osdscrub
set(unittest_osdscrub_srcs osd/TestOSDScrub.cc
    ${CMAKE_SOURCE_DIR}/src/common/util.cc)
add_executable(unittest_osdscrub
  ${unittest_osdscrub_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_osdscrub os common global osd ${BLKID_LIBRARIES}
  ${CMAKE_DL_LIBS} ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_osdscrub PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_osdscrub unittest_osdscrub)

# unittest_pglog
set(unittest_pglog_srcs osd/TestPGLog.cc)
add_executable(unittest_pglog
  ${unittest_pglog_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_pglog osd global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_pglog PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_pglog unittest_pglog)

# unittest_hitset
set(unittest_hitset_srcs osd/hitset.cc)
add_executable(unittest_hitset
  ${unittest_hitset_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_hitset osd global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_hitset PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_hitset unittest_hitset)

# unittest_osd_osdcap
set(unittest_osd_osdcap_srcs osd/osdcap.cc)
add_executable(unittest_osd_osdcap
  ${unittest_osd_osdcap_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_osd_osdcap osd global ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS} ${UNITTEST_LIBS})
set_target_properties(unittest_osd_osdcap PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_osd_osdcap unittest_osd_osdcap)

# unittest_chain_xattr
set(unittest_chain_xattr_srcs
  objectstore/chain_xattr.cc
  )
add_executable(unittest_chain_xattr
  ${unittest_chain_xattr_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
set_target_properties(unittest_chain_xattr PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
target_link_libraries(unittest_chain_xattr
  os
  global
  ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS}
  ${UNITTEST_LIBS}
  )
add_test(unittest_chain_xattr unittest_chain_xattr)

# unittest_flatindex
set(unittest_flatindex_srcs
  os/TestFlatIndex.cc
  )
add_executable(unittest_flatindex
  ${unittest_flatindex_srcs}
  $<TARGET_OBJECTS:heap_profiler_objs>
  )
target_link_libraries(unittest_flatindex
  os
  global
  ${CMAKE_DL_LIBS}
  ${TCMALLOC_LIBS}
  ${UNITTEST_LIBS}
  )
set_target_properties(unittest_flatindex PROPERTIES COMPILE_FLAGS
  ${UNITTEST_CXX_FLAGS})
add_test(unittest_flatindex unittest_flatindex)