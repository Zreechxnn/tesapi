#pragma once
#include <drogon/HttpController.h>

class Product
{
public:
  void getAll(const drogon::HttpRequestPtr &req,
              std::function<void(const drogon::HttpResponsePtr &)> &&callback);
};
