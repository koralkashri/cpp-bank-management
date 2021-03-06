#ifndef BANKMANAGEMENT_ACCOUNT_H
#define BANKMANAGEMENT_ACCOUNT_H

#include <string>
#include <vector>
#include <filesystem>
#include "plan.h"
#include "../../db/db_management.h"
#include "../../structures/output_logger_manager.h"
#include "../account_management_actions/account_transactions_management.h"

class account {
public:
    account(db_management *db_ptr, const std::string &account_name, output_logger_manager *output);
    ~account() = default;

    bool delete_account();

    void modify_free_cash(double cash);
    void transactions_management();
    void print_account_details() const;
    [[nodiscard]] std::string get_account_name() const;
    [[nodiscard]] std::vector<std::string> get_plan_names() const;
    void print_plan_details(const std::string &plan_name);
    void create_plan(const std::string &plan_name);
    void plan_management(const std::string &plan_name);
    void remove_plan(const std::string &plan_name);

    bool operator==(const std::string &name) const;
    bool operator!=(const std::string &name) const;

private:
    std::string account_name;
    db_management *db_ptr;
    output_logger_manager *output;

    account_transactions_management transactions;

    template<typename T>
    using plans_container = std::vector<T>;
    plans_container<plan> plans;

    plans_container<plan>::iterator find_plan(const std::string &name);
};

#endif //BANKMANAGEMENT_ACCOUNT_H