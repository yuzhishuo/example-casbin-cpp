/*
 * @Author: Leo
 * @Date: 2022-01-25 21:35:46
 * @LastEditTime: 2022-05-18 02:14:04
 * @LastEditors: Leo
 * @FilePath: /LedgerDB/main.cpp
 */

#include <iostream>
#include <memory>

#include <rocksdb/db.h>

#include "Spd.h"
#include "meta/User.h"
#include "rbac/AuthorityCertification.h"
#include "store/PersistenceStore.h"

// tmp
#include "interfaces/IUnique.h"
#include "meta/Ledgers.h"
#include "meta/Users.h"
#include <string>

#include <config/Config.h>
#include <raft_engine/RaftEngine.h>
#include <service/LedgerService.hpp>

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

namespace spd = spdlog;
using namespace std;
using namespace grpc;
namespace yuzhi {
class Ledger final : public IConfigurable {

public:
  Ledger() = default;
  virtual ~Ledger() {}
  virtual const char *Field() const override { return "ledger"; }

  void start() {

    auto &config = yuzhi::Config::Instance();
    auto prot = config.get<int>(this, "server_port");
    // grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    ServerBuilder builder;
    yuzhi::service::LedgerService ledgerService;
    std::string service_address = "[::]:" + to_string(prot);

    int selected_port = 0;
    // TODO: repeat listen port, need to fix
    builder.AddListeningPort(service_address, InsecureServerCredentials(),
                             &selected_port);
    // builder.set_health_check_service(new HealthCheckServiceImpl());
    builder.RegisterService(&ledgerService);
    auto server = builder.BuildAndStart();
    SPDLOG_INFO("start ledger service at {}", service_address);
    server->Wait();
  }
};
} // namespace yuzhi

int main(int argc, char **argv) {

  yuzhi::raft_engine::net::RaftService::Instance();
  yuzhi::Ledger ledger;
  ledger.start();

  return 0;
}
