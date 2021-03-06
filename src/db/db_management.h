#ifndef BANKMANAGEMENT_DB_MANAGEMENT_H
#define BANKMANAGEMENT_DB_MANAGEMENT_H

#include <string>
#include <vector>
#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include "plans_db_management.h"
#include "accounts_db_management.h"

class db_management {
public:
    db_management();

    // Accounts Management
    void create_account(const std::string &account_name);
    void delete_account(const std::string &account_name);
    void modify_account_free_cash(const std::string &account_name, double cash);
    [[nodiscard]] double get_account_free_cash(const std::string &account_name) const;

    // Account Transactions Management
    void update_account_monthly_income(const std::string &account_name, const std::string &source_name, double income);
    void set_account_single_time_income(const std::string &account_name, const std::string &source_name, double income);
    void pause_account_monthly_income(const std::string &account_name, const std::string &source_name);
    void restart_account_monthly_income(const std::string &account_name, const std::string &source_name);
    void update_account_monthly_outcome(const std::string &account_name, const std::string &target_name, double outcome);
    void set_account_single_time_outcome(const std::string &account_name, const std::string &target_name, double outcome);
    void pause_account_monthly_outcome(const std::string &account_name, const std::string &target_name);
    void restart_account_monthly_outcome(const std::string &account_name, const std::string &target_name);
    [[nodiscard]] std::vector<transaction> get_account_outcome_details(const std::string &account_name, const boost::gregorian::date &month) const;
    [[nodiscard]] std::vector<transaction> get_account_income_details(const std::string &account_name, const boost::gregorian::date &month) const;

    // Plans Management
    void create_plan(const std::string &account_name, const std::string &plan_name);
    double delete_plan(const std::string &account_name, const std::string &plan_name);
    void modify_plan_balance(const std::string &account_name, const std::string &plan_name, double cash);
    [[nodiscard]] double get_plan_balance(const std::string &account_name, const std::string &plan_name) const;
    [[nodiscard]] std::vector<std::string> get_all_accounts() const;
    [[nodiscard]] std::vector<std::string> get_all_account_plans(const std::string &account_name) const;

private:
    mongocxx::instance instance;
    mongocxx::client client;
    mongocxx::database db;
    plans_db_management plans_management;
    accounts_db_management accounts_management;

    [[nodiscard]] bool is_account_exists(const std::string &account_name) const;
};

#endif //BANKMANAGEMENT_DB_MANAGEMENT_H