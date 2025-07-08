#include "Product.h"
#include <json/json.h>
#include <fstream>

void Product::getAll(const drogon::HttpRequestPtr &req,
                     std::function<void(const drogon::HttpResponsePtr &)> &&callback)
{
    auto idStr = req->getParameter("id");

    std::ifstream file("../resources/products.json", std::ifstream::binary);
    if (!file.is_open())
    {
        Json::Value err;
        err["error"] = "File not found";
        callback(drogon::HttpResponse::newHttpJsonResponse(err));
        return;
    }

    Json::Value allProducts;
    file >> allProducts;
    if (idStr.empty())
    {
        callback(drogon::HttpResponse::newHttpJsonResponse(allProducts));
        return;
    }
    int targetId = std::stoi(idStr);
    for (const auto &item : allProducts)
    {
        if (item.isMember("id") && item["id"].asInt() == targetId)
        {
            callback(drogon::HttpResponse::newHttpJsonResponse(item));
            return;
        }
    }
    Json::Value notFound;
    notFound["error"] = "Product not found";
    callback(drogon::HttpResponse::newHttpJsonResponse(notFound));
}
