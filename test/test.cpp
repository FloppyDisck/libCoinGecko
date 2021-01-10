#include <gtest/gtest.h>
#include <string>
#include "coingecko.hpp"

std::vector<std::string> coinIDs = {"bitcoin", "ethereum"};
std::vector<std::string> currencies = {"usd", "eth"};
std::vector<std::string> exchanges = {"binance", "kraken"};
std::vector<std::string> contracts = {"0x9f8f72aa9304c8b593d555f12ef6589cc3a579a2"};
std::vector<std::string> indexes = {"BTC"};
std::vector<std::string> markets = {"balancer"};
std::vector<std::string> derivExchange = {"binance_futures"};

void assert_response(std::string res) {
    std::cout << res << std::endl;
    ASSERT_FALSE(res == "{}");
    ASSERT_FALSE(res == "{\"error\":\"Missing parameter ids\"}");
    ASSERT_FALSE(res == "{\"error\":\"Incorrect path. Please check https://www.coingecko.com/api/\"}");
}

TEST(Ping, ping) {
    auto res = coingecko::ping();
    assert_response(res);
}

TEST(Simple, price) {
    auto res = coingecko::price(coinIDs, currencies, true,
                                true, true, true);
    assert_response(res);
}

TEST(Simple, token_price) {
    auto res = coingecko::token_price(contracts, currencies, coingecko::ethereum, true,
                                      true, true, true);
    assert_response(res);
}

TEST(Simple, currencies) {
    auto res = coingecko::currencies();
    assert_response(res);
}

TEST(Coins, coins) {
    auto res = coingecko::coins();
    assert_response(res);
}

TEST(Coins, markets) {
    auto res = coingecko::markets(currencies, coinIDs, coingecko::decentralized_finance_defi,
                                  coingecko::market_cap_desc, 100, 1,
                                  true, {coingecko::day, coingecko::hour});
    assert_response(res);
}

TEST(Coins, coind_data) {
    auto res = coingecko::coin_data(coinIDs[0], true, true, true, true, true, true);
    assert_response(res);
}

TEST(Coins, coin_tickers) {
    auto res = coingecko::coin_tickers(coinIDs[0], exchanges, true, 1, true, coingecko::trust_score_desc);
    assert_response(res);
}

TEST(Coins, coin_history) {
    auto res = coingecko::coin_history(coinIDs[0], "08-01-2021", true);
    assert_response(res);
}

TEST(Coins, coin_market_chart_using_intervals) {
    auto res = coingecko::coin_market_chart(coinIDs[0], currencies[0], 4, coingecko::daily);
    assert_response(res);
}

TEST(Coins, coin_market_chart_using_intervals_and_max_flag) {
    auto res = coingecko::coin_market_chart(coinIDs[0], currencies[0], -1, coingecko::daily);
    assert_response(res);
}

TEST(Coins, coin_market_chart_using_timestamp) {
    auto res = coingecko::coin_market_chart(coinIDs[0], currencies[0],
                                            1610064000, 1610241549);
    assert_response(res);
}

TEST(Coins, coin_status_update) {
    auto res = coingecko::coin_status_update(coinIDs[0], 100, 1);
    assert_response(res);
}

TEST(Coins, coin_ohlc) {
    auto res = coingecko::coin_ohlc(coinIDs[1], currencies[0], 7);
    assert_response(res);
}

TEST(Contract, contract_data) {
    auto res = coingecko::contract_data(contracts[0]);
    assert_response(res);
}

TEST(Contract, contract_market_chart_using_intervals) {
    auto res = coingecko::contract_market_chart(contracts[0], currencies[0], 2);
    assert_response(res);
}

TEST(Contract, contract_market_chart_using_intervals_and_max_flag) {
    auto res = coingecko::contract_market_chart(contracts[0], currencies[0], -1);
    assert_response(res);
}

TEST(Contract, contract_market_chart_using_intervals_using_timestamp) {
    auto res = coingecko::contract_market_chart(contracts[0], currencies[0],
                                                1610064000, 1610241549);
    assert_response(res);
}

TEST(Exchange, exchanges_full) {
    auto res = coingecko::exchanges_full(100, 1);
    assert_response(res);
}

TEST(Exchange, exchanges) {
    auto res = coingecko::exchanges();
    assert_response(res);
}

TEST(Exchange, exchange_overview) {
    auto res = coingecko::exchange_overview(exchanges[0]);
    assert_response(res);
}

TEST(Exchange, exchange_tickers) {
    auto res = coingecko::exchange_tickers(exchanges[0], coinIDs, true, 1, true);
    assert_response(res);
}

TEST(Exchange, exchange_status_update) {
    auto res = coingecko::exchange_status_update(exchanges[0], 100, 1);
    assert_response(res);
}

TEST(Exchange, exchange_volume_chart) {
    auto res = coingecko::exchange_volume_chart(exchanges[0], 2);
    assert_response(res);
}

TEST(Finance, finance_platforms) {
    auto res = coingecko::finance_platforms(100, 1);
    assert_response(res);
}

TEST(Finance, finance_products) {
    auto res = coingecko::finance_products(0, 0, 100, 1);
    assert_response(res);
}

TEST(Indexes, market_indexes) {
    auto res = coingecko::market_indexes(100, 1);
    assert_response(res);
}

TEST(Indexes, market_indexes_names) {
    auto res = coingecko::market_indexes_names();
    assert_response(res);
}

TEST(Indexes, get_market_index) {
    //TODO: Not working, contact CoinGecko
    auto res = coingecko::get_market_index(markets[0], indexes[0]);
    assert_response(res);
}

TEST(Indexes, get_market_index_alt) {
    //TODO: Not working, contact CoinGecko
    auto res = coingecko::get_market_index_alt(markets[0], indexes[0]);
    assert_response(res);
}

TEST(Derivatives, derivative_tickers) {
    auto res = coingecko::derivative_tickers();
    assert_response(res);
}

TEST(Derivatives, derivative_exchanges) {
    auto res = coingecko::derivative_exchanges(coingecko::name_asc, 100, 1);
    assert_response(res);
}

TEST(Derivatives, derivative_exchange_data) {
    auto res = coingecko::derivative_exchange_data(derivExchange[0]);
    assert_response(res);
}

TEST(Derivatives, derivative_exchanges_names) {
    auto res = coingecko::derivative_exchanges_names();
    assert_response(res);
}

TEST(Status, status_updates) {
    auto res = coingecko::status_updates(coingecko::general, coingecko::both, 100, 1);
    assert_response(res);
}

TEST(Events, events) {
    auto res = coingecko::events("US", "Conference", 1, true, "2021-01-01", "2021-01-08");
    assert_response(res);
}

TEST(Events, event_countries) {
    auto res = coingecko::event_countries();
    assert_response(res);
}

TEST(Events, events_types) {
    auto res = coingecko::event_types();
    assert_response(res);
}

TEST(Exchange_Rates, exchange_rates) {
    auto res = coingecko::exchange_rates();
    assert_response(res);
}

TEST(Trending, trending) {
    auto res = coingecko::trending();
    assert_response(res);
}

TEST(Global, global_data) {
    auto res = coingecko::global_data();
    assert_response(res);
}

TEST(Global, global_defi_data) {
    auto res = coingecko::global_defi_data();
    assert_response(res);
}