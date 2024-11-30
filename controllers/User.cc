#include "User.h"

void User::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    // write your application logic here
}

#include <drogon/HttpController.h>
#include <drogon/orm/Mapper.h>
#include <bcrypt.h> // Библиотека для хеширования паролей

using namespace drogon;
using namespace drogon::orm;

class User : public drogon::HttpController<User> {
public:
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(User::registerUser, "/register", Post);
    METHOD_LIST_END

        void registerUser(const HttpRequestPtr& req,
            std::function<void(const HttpResponsePtr&)>&& callback) {
        auto email = req->getParameter("email");
        auto password = req->getParameter("password");

        // Хеширование пароля
        char salt[BCRYPT_HASHSIZE];
        char hash[BCRYPT_HASHSIZE];
        bcrypt_gensalt(12, salt);
        bcrypt_hashpw(password.c_str(), salt, hash);

        // Сохранение в базу данных
        Mapper<drogon_model::your_namespace::Account> accountMapper(app().getDbClient());
        drogon_model::your_namespace::Account newAccount;
        newAccount.setEmail(email);
        newAccount.setPassHash(hash);

        try {
            accountMapper.insert(newAccount);
            auto resp = HttpResponse::newHttpResponse();
            resp->setBody("Registration successful!");
            callback(resp);
        }
        catch (const DrogonDbException& e) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k500InternalServerError);
            resp->setBody("Registration failed!");
            callback(resp);
        }
    }
};
