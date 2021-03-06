#ifndef BANKMANAGEMENT_ACCOUNT_TRANSACTIONS_DB_MANAGEMENT_H
#define BANKMANAGEMENT_ACCOUNT_TRANSACTIONS_DB_MANAGEMENT_H

#include <string>
#include <vector>
#include <boost/date_time.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include "../program_flow/structures/transaction.h"
#include "filters/db_account_transactions_filter.h"
#include "filters/tools/db_filter.h"

class accounts_db_management;

class account_transactions_db_management {
public:
    explicit account_transactions_db_management(mongocxx::database *db_ptr, accounts_db_management *accounts_db_m);

    /// Will store the income details for the current month
    void update_account_monthly_income(const std::string &account_name, const std::string &source_name, double income);

    /// Will store the income details for the current month
    void set_account_single_time_income(const std::string &account_name, const std::string &source_name, double income);

    void pause_account_monthly_income(const std::string &account_name, const std::string &source_name);

    void restart_account_monthly_income(const std::string &account_name, const std::string &source_name);

    /// Will store the outcome details for the current month
    void update_account_monthly_outcome(const std::string &account_name, const std::string &target_name, double outcome);

    /// Will store the outcome details for the current month
    void set_account_single_time_outcome(const std::string &account_name, const std::string &target_name, double outcome);

    void pause_account_monthly_outcome(const std::string &account_name, const std::string &target_name);

    void restart_account_monthly_outcome(const std::string &account_name, const std::string &target_name);

    [[nodiscard]] std::vector<transaction> get_account_outcome_details(const std::string &account_name,
                                                                       const boost::gregorian::date &month) const;

    [[nodiscard]] std::vector<transaction> get_account_income_details(const std::string &account_name,
                                                                      const boost::gregorian::date &month) const;

    [[nodiscard]] static std::string get_date_for_db(const boost::gregorian::date &date);

private:
    mongocxx::database *db_ptr;
    accounts_db_management *accounts_db_m;
    std::string transactions_db_field_name;
    db_filter expanded_filter;
    db_account_transactions_filter transactions_filter;

    [[nodiscard]] bool is_transaction_exists(const std::string &account_name, const transaction_id &id) const;

    void update_or_create_account_transaction(const std::string &account_name, const transaction &transaction_data);

    void change_account_transaction_state(const std::string &account_name, const transaction_id &id, bool is_active);

    [[nodiscard]] std::vector<transaction> get_account_transactions_details(const std::string &account_name,
                                                                            const boost::gregorian::date &month,
                                                                            bool is_income) const;

    void update_account_transaction(const std::string &account_name, const transaction &transaction_data);

    void create_account_transaction(const std::string &account_name, const transaction &transaction_data);
};

#endif //BANKMANAGEMENT_ACCOUNT_TRANSACTIONS_DB_MANAGEMENT_H