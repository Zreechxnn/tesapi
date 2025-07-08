#include <drogon/drogon.h>
#include "controllers/product.h"

int main()
{
    Product controller;

    drogon::app()
        .registerHandler("/products",
                         [&controller](const drogon::HttpRequestPtr &req,
                                       std::function<void(const drogon::HttpResponsePtr &)> &&callback)
                         {
                             controller.getAll(req, std::move(callback));
                         },
                         {drogon::Get})
        .addListener("0.0.0.0", 8080)
        .run();
}
