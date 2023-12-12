#include<iostream>
#include<memory>
#include<string>
#include<grpc++/grpc++.h>

#include "helloservice.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using hello::req;
using hello::res;
using hello::helloservice;

class Client{

    public :
    client(std::shared_ptr<Channel>channel):stub_(helloservice::NewStub(channel)){}

    std::string sayhello(const std::string& name){
        req request;
        request.set_name(name);

        res response;
        ClientContext context;

        Status status=stub_->sayhell(&context, request,&response);

        if(status.ok()){
            return respones.message;
        }
        else{
            return "rpc failed";
        }

    }

    private:

    std::unique_ptr<helloservice::Stub>stub_;

};

int main()
{
    Client client (grpc::CreateChannel("localhost:50051",grpc::InsecureChannelCredentials()));
    std::string user("venkat");
    std::string reply client.sayhello(user);
    std::cout<<"received"<<reply<<std::endl;
    return 0;
}

