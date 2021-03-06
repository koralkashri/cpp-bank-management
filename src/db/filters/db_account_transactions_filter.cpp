#include "db_account_transactions_filter.h"
#include <sstream>
#include "../account_transactions_db_management.h"

using namespace std::string_literals;

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::sub_array;
using bsoncxx::builder::basic::sub_document;
using bsoncxx::builder::basic::document;
using bsoncxx::builder::basic::array;

db_account_transactions_filter::db_account_transactions_filter(std::string transactions_db_field_name)
        : transactions_db_field_name(std::move(transactions_db_field_name)) {
    archive_field_name = "archive";
}

void db_account_transactions_filter::filter_by_id(document &filter, const std::string &transactions_hierarchy, const transaction_id &t_id) const {
    std::vector<filter_field> fields;
    fields.emplace_back(transactions_hierarchy + transactions_db_field_name);
    fields.back()
            .add_sub_field("transaction_name_id"s, t_id.transaction_name)
            .add_sub_field("is_income"s, t_id.is_income);

    db_filter::make_regular_filter_on_arrays(filter, fields);
}

void db_account_transactions_filter::filter_by_is_income(document &filter, const std::string &transactions_hierarchy,
                                                         bool is_income) const {
    std::vector<filter_field> fields;
    fields.emplace_back(transactions_hierarchy + transactions_db_field_name);
    fields.back()
            .add_sub_field("is_income"s, is_income);

    db_filter::make_regular_filter_on_arrays(filter, fields);
}

void db_account_transactions_filter::filter_archive_by_date(document &filter, const std::string &archive_hierarchy,
                                                            const boost::gregorian::date &date) const {
    std::vector<filter_field> fields;
    fields.emplace_back(archive_hierarchy + archive_field_name);
    fields.back()
            .add_sub_field("month"s, account_transactions_db_management::get_date_for_db(date));

    db_filter::make_regular_filter_on_arrays(filter, fields);
}

void db_account_transactions_filter::aggregate_filter_by_is_income(document &filter,
                                                                   const std::string &transactions_hierarchy,
                                                                   bool is_income) const {
    db_filter::make_aggregate_filter(filter,
                          transactions_hierarchy + transactions_db_field_name,
                          "is_income", is_income);
}

void
db_account_transactions_filter::aggregate_filter_archive_by_date(document &filter, const std::string &archive_hierarchy,
                                                                 const boost::gregorian::date &date) const {
    db_filter::make_aggregate_filter(filter,
                          archive_hierarchy + archive_field_name,
                          "month", account_transactions_db_management::get_date_for_db(date));
}