#include<iostream>
#include<string>
#include<memory>

#include<grpc++/grpc++.h>

#include "helloservice.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using hello::req;
using hello::res;
using hello::helloservice;


class HelloserviceImpl final :public hello::helloservice
{
    Status sayhello(ServerContext* context, const req* request,res* response) override{
        std::string prefix("Hello ");
        response->set_message(prefix+ request->name());
        return Status::OK;
    }
};


void RunServer()
{
    std::string server_address("0.0.0.0:50051");
    HelloserviceImpl service;
    ServerBuilder builder;
    builder.AddListeningport(server_address,grpc::InsecureServiceCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout<<"server listening port "<<server_address<<std::endl;
    server->Wait();
}

int main()
{
    RunServer();
    return 0;
}