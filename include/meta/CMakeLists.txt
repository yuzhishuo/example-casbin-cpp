

add_library(meta Ledger.cpp
                 Ledgers.cpp
                 User.cpp
                 Users.cpp
                 UsersImpl.cpp
                 LedgersImpl.cpp
                 )
target_link_libraries(meta
                 RocksDB::rocksdb
                 fmt::fmt)