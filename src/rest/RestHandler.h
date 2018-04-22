//
// Created by nuno on 30-03-2018.
//

#ifndef LABC_RESTHANDLER_H
#define LABC_RESTHANDLER_H

#include <memory>
#include <http.h>
#include <endpoint.h>

class RestHandler : public Pistache::Http::Handler, public std::enable_shared_from_this<RestHandler> {

HTTP_PROTOTYPE(RestHandler)

private:
    Pistache::Address address;
    Pistache::Http::Endpoint server;

public:

    std::shared_ptr<RestHandler> getPointer() {
        return shared_from_this();
    }

    RestHandler() : address(Pistache::Ipv4::any(), Pistache::Port(9080)), server(address) {

        auto opts = Pistache::Http::Endpoint::options();

        opts.threads(10);

        server.init(opts);

    }

    ~RestHandler() {

        server.shutdown();


    }

    void start() {
        server.setHandler(getPointer());

        server.serveThreaded();
    }

    void onRequest(const Pistache::Http::Request &request, Pistache::Http::ResponseWriter response) override;

};


#endif //LABC_RESTHANDLER_H
