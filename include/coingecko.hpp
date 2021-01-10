#ifndef LIBCOINGECKO_HPP
#define LIBCOINGECKO_HPP
#include <httplib.h>

namespace coingecko {

    using response = std::string;

    enum platforms { ethereum=0 };

    enum coin_category { decentralized_finance_defi=0 };

    enum market_sort_order { market_cap_desc=0, gecko_desc=1, gecko_asc=2, market_cap_asc=3,
                      volume_asc=4, m_volume_desc=5, id_asc=6, id_desc=7};

    enum price_range { hour=0, day=1, week=2, week2=3, day30=4, day200=5, year=6 };

    enum sort_order { trust_score_desc=0, trust_score_asc=1, volume_desc=2 };

    enum data_intervals { minutely=0, hourly=1, daily=2 };

    enum includes { all=0, unexpired=1 };

    enum derivative_order { name_asc=0, name_desc=1, open_interest_btc_asc=2, open_interest_btc_desc=3,
            trade_volume_24h_btc_asc=4, trade_volume_24h_btc_desc=5 };

    enum status_category { general=0, milestone=1, partnership=2, exchange_listing=3, software_release=4,
            fund_movement=5, new_listings=6, event=7 };

    enum project_type { both=0, coin=1, market=2 };

    // Enumerator converters
    inline std::string _to_str(platforms platform) {
        switch(platform) {
            case 0:
                return "ethereum";
            default:
                return "";
        }
    }

    inline std::string _to_str(coin_category category) {
        switch (category) {
            case 0:
                return "decentralized_finance_defi";
            default:
                return "";
        }
    }

    inline std::string _to_str(market_sort_order order) {
        switch (order) {
            case 0:
                return "market_cap_desc";
            case 1:
                return "gecko_desc";
            case 2:
                return "gecko_asc";
            case 3:
                return "market_cap_asc";
            case 4:
                return "volume_asc";
            case 5:
                return "volume_desc";
            case 6:
                return "id_asc";
            case 7:
                return "id_desc";
            default:
                return "";
        }
    }

    inline std::string _to_str(price_range range) {
        switch (range) {
            case 0:
                return "1h";
            case 1:
                return "24h";
            case 2:
                return "7d";
            case 3:
                return "14d";
            case 4:
                return "30d";
            case 5:
                return "200d";
            case 6:
                return "1y";
            default:
                return "";
        }
    }

    inline std::string _to_str(sort_order order) {
        switch (order) {
            case 0:
                return "trust_score_desc";
            case 1:
                return "trust_score_asc";
            case 2:
                return "volume_desc";
            default:
                return "";
        }
    }

    inline std::string _to_str(data_intervals intervals) {
        switch (intervals) {
            case 0:
                return "minutely";
            case 1:
                return "hourly";
            case 2:
                return "daily";
            default:
                return "";
        }
    }

    inline std::string _to_str(includes includes) {
        switch (includes) {
            case 0:
                return "all";
            case 1:
                return "unexpired";
            default:
                return "";
        }
    }

    inline std::string _to_str(derivative_order order) {
        switch (order) {
            case 0:
                return "name_asc";
            case 1:
                return "name_desc";
            case 2:
                return "open_interest_btc_asc";
            case 3:
                return "open_interest_btc_desc";
            case 4:
                return "trade_volume_24h_btc_asc";
            case 5:
                return "trade_volume_24h_btc_desc";
            default:
                return "";
        }
    }

    inline std::string _to_str(status_category category) {
        switch (category) {
            case 0:
                return "general";
            case 1:
                return "milestone";
            case 2:
                return "partnership";
            case 3:
                return "exchange_listing";
            case 4:
                return "software_release";
            case 5:
                return "fund_movement";
            case 6:
                return "new_listings";
            case 7:
                return "event";
            default:
                return "";
        }
    }

    inline std::string _to_str(project_type type) {
        switch (type) {
            case 0:
                return "";
            case 1:
                return "coin";
            case 2:
                return "market";
            default:
                return "";
        }
    }

    // Some predefined strings
    static const std::string sTrue = "true";
    static const std::string sFalse = "false";

    inline response geckoRequest(const std::string& request) {
        //TODO: dont initialize every time
        httplib::Client coingeckoClient("https://api.coingecko.com");
        auto answer = coingeckoClient.Get(request.c_str());
        // If head null return a generic bad answer
        return answer->body;
    }

    //ping

    /**
     * Check the API server status.
     * See: /ping
     *
     * @return server status
     */
    inline response ping() {
        std::string request = "/ping";
        return geckoRequest(request);
    }

    //simple

    /**
     * Get the current price of any cryptocurrencies in any other supported currencies that you need.
     * See: /simple/price
     *
     * @param coinIDs ID of coins, refers coingecko::coins
     * @param currencies currency of coins, refers to coingecko::currencies
     * @param include_market_cap Include market cap
     * @param include_24hr_vol Include 24 hour volume
     * @param include_24hr_change Include 24 hour change
     * @param include_last_updated_at Include last updated value time stamp
     * @return price(s) of cryptocurrency
     */
    response price(const std::vector<std::string>& coinIDs,
                   const std::vector<std::string>& currencies,
                   bool include_market_cap = false, bool include_24hr_vol = false,
                   bool include_24hr_change = false, bool include_last_updated_at = false) {

        std::string request = "/api/v3/simple/price?";

        request += "ids=";
        for (const std::string& coin : coinIDs) {
            request += coin + ",";
        }
        request += "&vs_currencies=";
        for (const std::string& currency : currencies) {
            request += currency + ",";
        }

        request += "&include_market_cap=" + (include_market_cap?sTrue:sFalse);
        request += "&include_24hr_vol=" + (include_24hr_vol?sTrue:sFalse);
        request += "&include_24hr_change=" + (include_24hr_change?sTrue:sFalse);
        request += "&include_last_updated_at=" + (include_last_updated_at?sTrue:sFalse);

        return geckoRequest(request);
    }

    /**
     * Get current price of tokens (using contract addresses) for a given platform in any other currency that you need.
     * See: /simple/token_price/{platformID}
     *
     * @param contract_addresses The contract address of tokens
     * @param currencies currency of coins, refers to coingecko::currencies
     * @param platformID The ID of the platform issuing tokens (Only ethereum is supported for now)
     * @param include_market_cap Include market cap
     * @param include_24hr_vol Include 24 hour volume
     * @param include_24hr_change Include 24 hour change
     * @param include_last_updated_at Include last updated value time stamp
     * @return price(s) of cryptocurrency
     */
    response token_price(const std::vector<std::string>& contract_addresses,
                         const std::vector<std::string>& currencies,
                         platforms platformID = ethereum,
                         bool include_market_cap = false, bool include_24hr_vol = false,
                         bool include_24hr_change = false, bool include_last_updated_at = false) {

        std::string request = "/api/v3/simple/token_price/";
        request += _to_str(platformID) + "?";

        request += "contract_addresses=";
        for (const std::string& address : contract_addresses) {
            request += address + ",";
        }

        request += "&vs_currencies=";
        for (const std::string& currency : currencies) {
            request += currency + ",";
        }

        request += "&include_market_cap=" + (include_market_cap?sTrue:sFalse);
        request += "&include_24hr_vol=" + (include_24hr_vol?sTrue:sFalse);
        request += "&include_24hr_change=" + (include_24hr_change?sTrue:sFalse);
        request += "&include_last_updated_at=" + (include_last_updated_at?sTrue:sFalse);

        return geckoRequest(request);
    }

    /**
     * Get list of supported currencies
     * See: /simple/supported_vs_currencies
     *
     * @return list of supported_vs_currencies.
     */
    response currencies() {
        std::string request = "/api/v3/simple/supported_vs_currencies";

        return geckoRequest(request);
    }

    //coins

    /**
     * List all supported coins id, name and symbol
     * See: /coins/list
     *
     * @return List all coins with id, name, and symbol
     */
    response coins() {
        std::string request = "/api/v3/coins/list";

        return geckoRequest(request);
    }

    /**
     * Used to obtain coins market data
     * See: /coins/markets
     *
     * @param currencies currency of coins, refers to coingecko::currencies
     * @param coinIDs ID of coins, refers coingecko::coins - can be left empty
     * @param category Filter by coin category
     * @param order Sort results by field
     * @param per_page Total results per page {1 - 250}
     * @param page Current page
     * @param sparkline Include sparkline 7 days data
     * @param price_change_percentage Change percentages
     * @return List all coins with market data
     */
    response markets(const std::vector<std::string>& currencies,
                     const std::vector<std::string>& coinIDs,
                     coin_category category = decentralized_finance_defi,
                     market_sort_order order = market_cap_desc,
                     int per_page = 100, int page = 1, bool sparkline = false,
                     const std::vector<price_range>& price_change_percentage = {day}) {
        std::string request = "/api/v3/coins/markets?";

        if (!coinIDs.empty()) {
            request += "ids=";
            for (const std::string& coin : coinIDs) {
                request += coin + ",";
            }
        }

        request += "&vs_currencies=";
        for (const std::string& currency : currencies) {
            request += currency + ",";
        }

        request += "&category=" + _to_str(category);
        request += "&order" + _to_str(order);
        request += "&per_page=" + std::to_string(per_page);
        request += "&page=" + std::to_string(page);
        request += "&sparkline=" + (sparkline?sTrue:sFalse);

        request += "&price_range_percentage=";
        for (const price_range& range : price_change_percentage) {
            request += _to_str(range) + ",";
        }

        return geckoRequest(request);
    }

    /**
     * Get current coin data
     * See: /coins/{id}
     *
     * @param coinID ID of coin, refers coingecko::coins
     * @param localization Include all localized languages in response
     * @param tickers Include tickers data
     * @param market_data Include market data
     * @param community_data Include community data
     * @param developer_data Include developer data
     * @param sparkline Include sparkline 7 days data
     * @return Get current data for a coin
     */
    response coin_data(const std::string& coinID, bool localization=true, bool tickers=true,
                       bool market_data=true, bool community_data=true, bool developer_data=true,
                       bool sparkline=true) {
        std::string request = "/api/v3/coins/" + coinID + "?";

        request += "&localization=" + (localization?sTrue:sFalse);
        request += "&tickers=" + (tickers?sTrue:sFalse);
        request += "&market_data=" + (market_data?sTrue:sFalse);
        request += "&community_data=" + (community_data?sTrue:sFalse);
        request += "&developer_data=" + (developer_data?sTrue:sFalse);
        request += "&sparkline=" + (sparkline?sTrue:sFalse);

        return geckoRequest(request);
    }

    /**
     *  Get coin tickers, paginated to 100
     *  See: /coins/{id}/tickers
     *
     * @param coinID ID of coin, refers coingecko::coins
     * @param exchangeIDs Filter results with exchangeIDs, refers to coingecko::exchanges can be empty
     * @param include_exchange_logo Show exchange logo
     * @param page Results page
     * @param depth show 2% orderbook depth
     * @param order Sort order
     * @return Get coin tickers
     */
    response coin_tickers(const std::string& coinID, const std::vector<std::string>& exchangeIDs,
                          bool include_exchange_logo, int page, bool depth=true,
                          sort_order order = trust_score_desc) {
        std::string request = "/api/v3/coins/" + coinID + "/tickers?";

        request += "exchange_ids=";
        for (const std::string& id : exchangeIDs) {
            request += id + ",";
        }

        request += "&include_exchange_logo=" + (include_exchange_logo?sTrue:sFalse);
        request += "&page=" + std::to_string(page);
        request += "&depth=" + (depth?sTrue:sFalse);
        request += "&order=" + _to_str(order);

        return geckoRequest(request);
    }

    /**
     * Get historical data at a given date
     * See: /coins/{id}/history
     *
     * @param coinID ID of coin, refers coingecko::coins
     * @param date Must be in dd-mm-yyyy format
     * @param localization Include localized languages
     * @return Get historical data at a given date for a coin
     */
    response coin_history(const std::string& coinID, const std::string& date, bool localization) {
        std::string request = "/api/v3/coins/" + coinID + "/history?";

        request += "&date=" + date;
        request += "&localization=" + (localization?sTrue:sFalse);

        return geckoRequest(request);
    }

    /**
     * Get historical market data include price, market cap, and 24h volume (granularity auto)
     * See: /coins/{id}/market_chart
     *
     * @param coinID ID of coin, refers coingecko::coins
     * @param currency currency of coins, refers to coingecko::currencies
     * @param days Data up to numbers of days ago, max=-1
     * @param interval Data intervals
     * @return Get historical market data include price, market cap, and 24h volume
     */
    response coin_market_chart(const std::string& coinID, const std::string& currency, int days,
                              data_intervals interval = daily) {
        std::string request = "/api/v3/coins/" + coinID + "/market_chart?";

        request += "vs_currency=" + currency;
        request += "&days=" + (days==-1?"max":std::to_string(days));
        request += "&interval" + _to_str(interval);

        return geckoRequest(request);
    }

    /**
     * Get historical market data include price, market cap, and 24h volume (granularity auto)
     * See: /coins/{id}/market_chart/range
     *
     * @param coinID ID of coin, refers coingecko::coins
     * @param currency currency of coins, refers to coingecko::currencies
     * @param from Unix time stamp
     * @param to Unix time stamp
     * @return Get historical market data include price, market cap, and 24h volume
     */
    response coin_market_chart(const std::string& coinID, const std::string& currency, int from, int to) {
        std::string request = "/api/v3/coins/" + coinID + "/market_chart/range?";

        request += "vs_currency=" + currency;
        request += "&from=" + std::to_string(from);
        request += "&to=" + std::to_string(to);

        return geckoRequest(request);
    }

    /**
     * Get status updates for a given coin
     * See: /coins/{id}/status_updates
     *
     * @param coinID ID of coin, refers coingecko::coins
     * @param per_page Total results per page
     * @param page Results page
     * @return Get paginated status updates for a given coin
     */
    response coin_status_update(const std::string& coinID, int per_page, int page) {
        std::string request = "/api/v3/coins/" + coinID + "/status_updates?";

        request += "&per_page=" + std::to_string(per_page);
        request += "&page=" + std::to_string(page);

        return geckoRequest(request);
    }

    /**
     * Get coins OHLC
     * See: /coins/{id}/ohlc
     *
     * Candle’s body:
     * 1 - 2 days: 30 minutes
     * 3 - 30 days: 4 hours
     * 31 and before: 4 days
     *
     * @param coinID ID of coin, refers coingecko::coins
     * @param currency currency of coins, refers to coingecko::currencies
     * @param days Number of days ago; -1 = max; can only be 1/7/14/30/90/180/365
     * @return Each candle is formated as [time, open, high, low, close]
     */
    response coin_ohlc(const std::string& coinID, const std::string& currency, int days) {
        std::string request = "/api/v3/coins/" + coinID + "/ohlc?";

        request += "&vs_currency=" + currency;
        request += "&days=" + (days==-1?"max":std::to_string(days));

        return geckoRequest(request);
    }

    //contract

    /**
     * Get coin info from contract address
     * See: /coins/{id}/contract/{contract_address}
     *
     * @param contract_address The contract address of tokens
     * @param platformID The ID of the platform issuing tokens (Only ethereum is supported for now)
     * @return Get current data for a coin
     */
    response contract_data(const std::string& contract_address, platforms platformID = ethereum) {
        std::string request = "/api/v3/coins/" + _to_str(platformID) + "/contract/" + contract_address + "?";

        return geckoRequest(request);
    }

    /**
     * Get historical market data include price, market cap, and 24h volume (granularity auto)
     * See: /coins/{id}/contract/{contract_address}/market_chart/
     *
     * @param contract_address The contract address of tokens
     * @param currency currency of coins, refers to coingecko::currencies
     * @param Number of days ago; -1 = max
     * @param platformID The ID of the platform issuing tokens (Only ethereum is supported for now)
     * @return Get historical market data include price, market cap, and 24h volume
     */
    response contract_market_chart(const std::string& contract_address, const std::string& currency,
                                   int days, platforms platformID = ethereum) {

        std::string request = "/api/v3/coins/" + _to_str(platformID) + "/contract/" + contract_address + "/market_chart?";

        request += "vs_currency=" + currency;
        request += "&days=" + (days==-1?"max":std::to_string(days));

        return geckoRequest(request);
    }

    /**
     * Get historical market data include price, market cap, and 24h volume within a range of timestamp (granularity auto)
     * See: /coins/{id}/contract/{contract_address}/market_chart/range
     *
     * @param contract_address The contract address of tokens
     * @param currency currency of coins, refers to coingecko::currencies
     * @param from Unix time stamp
     * @param to Unix time stamp
     * @param platformID The ID of the platform issuing tokens (Only ethereum is supported for now)
     * @return Get historical market data include price, market cap, and 24h volume
     */
    response contract_market_chart(const std::string& contract_address,
                                   const std::string& currency, int from, int to,
                                   platforms platformID = ethereum) {
        std::string request = "/api/v3/coins/" + _to_str(platformID) + "/contract/" + contract_address + "/market_chart/range?";

        request += "&vs_currency=" + currency;
        request += "&from=" + std::to_string(from);
        request += "&to=" + std::to_string(to);

        return geckoRequest(request);
    }

    //exchange

    /**
     * List all exchanges with all information
     * See: /exchanges
     *
     * @param per_page Total results per page {1 - 250}
     * @param page Results page
     * @return List all exchanges
     */
    response exchanges_full(int per_page, int page) {
        std::string request = "/api/v3/exchanges?";

        request += "&per_page=" + std::to_string(per_page);
        request += "&page=" + std::to_string(page);

        return geckoRequest(request);
    }

    /**
     * List all exchanges id and name
     * See: /exchanges/list
     *
     * @return List all coins with id and name
     */
    response exchanges() {
        std::string request = "/api/v3/exchanges/list";

        return geckoRequest(request);
    }

    /**
     * Get exchange volume in BTW and tickers
     * See: /exchanges/{id}
     *
     * @param exchangeID ID representing exchange, refers to coingecko::exchanges
     * @return Get exchange volume in BTC and top 100 tickers
     */
    response exchange_overview(const std::string& exchangeID) {
        std::string request = "/api/v3/exchanges/" + exchangeID;

        return geckoRequest(request);
    }

    /**
     * Get exchange tickers (paginated 100 per page)
     * See: /exchanges/{id}/tickers
     *
     * @param exchangeID ID representing exchange, refers to coingecko::exchanges
     * @param coinIDs ID of coins, refers coingecko::coins
     * @param include_exchange_logo Show exchange logo
     * @param page Results page
     * @param depth show 2% orderbook depth
     * @param order Sort results by field
     * @return Get exchange tickers
     */
    response exchange_tickers(const std::string& exchangeID, const std::vector<std::string>& coinIDs,
                              bool include_exchange_logo, int page, bool depth,
                              sort_order order = trust_score_desc) {
        std::string request = "/api/v3/exchanges/" + exchangeID + "/tickers?";

        request += "coin_ids=";
        for (const std::string& id : coinIDs) {
            request += id + ",";
        }

        request += "&include_exchange_logo=" + (include_exchange_logo?sTrue:sFalse);
        request += "&page=" + std::to_string(page);
        request += "&depth=" + (depth?sTrue:sFalse);
        request += "&order=" + _to_str(order);

        return geckoRequest(request);
    }

    /**
     * Get status updates for a given exchange
     * See: /exchanges/{id}/status_updates
     *
     * @param exchangeID ID representing exchange, refers to coingecko::exchanges
     * @param per_page Total results per page {1 - 250}
     * @param page Results page
     * @return Get paginated status updates for a given coin
     */
    response exchange_status_update(const std::string& exchangeID, int per_page = 100, int page = 1) {
        std::string request = "/api/v3/exchanges/" + exchangeID + "/status_updates/?";

        request += "&per_page=" + std::to_string(per_page);
        request += "&page=" + std::to_string(page);

        return geckoRequest(request);
    }

    /**
     * Get volume chart data for a given exchange
     * See: /exchanges/{id}/volume_chart
     *
     * @param exchangeID ID representing exchange, refers to coingecko::exchanges
     * @param Number of days ago; -1 = max
     * @return Get exchange volume_chart data
     */
    response exchange_volume_chart(const std::string& exchangeID, int days) {

        std::string request = "/api/v3/exchanges/" + exchangeID + "/volume_chart?";

        request += "&days=" + (days==-1?"max":std::to_string(days));

        return geckoRequest(request);
    }

    //finance

    /**
     * List all finance platforms
     * See: /finance_platforms
     *
     * @param per_page Total results per page {1 - 250}
     * @param page Results page
     * @return List all finance platforms
     */
    response finance_platforms(int per_page = 100, int page = 1) {
        std::string request = "/api/v3/finance_platforms?";

        request += "&per_page=" + std::to_string(per_page);
        request += "&page=" + std::to_string(page);

        return geckoRequest(request);
    }

    /**
     * List all finance products
     * See: /finance_products
     *
     * @param start_at Start date - Documentation doesnt explain
     * @param end_at End date - Documentation doesnt explain
     * @param per_page Total results per page {1 - 250}
     * @param page Results page
     * @return List all finance products
     */
    response finance_products(int start_at, int end_at, int per_page = 100, int page = 1) {
        std::string request = "/api/v3/finance_products?";

        request += "&per_page=" + std::to_string(per_page);
        request += "&page=" + std::to_string(page);
        // This releases an internal server error
        //request += "&start_at=" + std::to_string(start_at);
        //request += "&end_at=" + std::to_string(end_at);

        return geckoRequest(request);
    }

    //indexes

    /**
     * List all market indexes
     * See: /indexes
     *
     * @param per_page Total results per page {1 - 250}
     * @param page Results page
     * @return List all market indexes
     */
    response market_indexes(int per_page = 100, int page = 1) {
        std::string request = "/api/v3/indexes?";

        request += "&per_page=" + std::to_string(per_page);
        request += "&page=" + std::to_string(page);

        return geckoRequest(request);
    }

    /**
     * List all market indexes by id and name
     * See: /indexes/list
     *
     * @return list market indexes id and name
     */
    response market_indexes_names() {
        std::string request = "/api/v3//indexes/list";

        return geckoRequest(request);
    }

    /**
     * Get market index by market id and index id
     * See: /indexes/{market_id}/{id}
     *
     * @param marketID Market ID from coingecko::exchanges
     * @param indexID Index ID from coingecko::market_indexes
     * @return get market index by market id and index id
     */
    response get_market_index(const std::string& marketID, const std::string& indexID) {
        std::string request = "/api/v3/indexes/" + marketID + "/" + indexID;

        return geckoRequest(request);
    }

    /**
     * Get market index by market id and index id
     * See: /indexes/list_by_market_and_id/{market_id}/{id}
     *
     * @param marketID Market ID from coingecko::exchanges
     * @param indexID Index ID from coingecko::market_indexes
     * @return get market index by id and market id
     */
    response get_market_index_alt(const std::string& marketID, const std::string& indexID) {
        std::string request = "/api/v3/indexes/list_by_market_and_id/" + marketID + "/" + indexID;

        return geckoRequest(request);
    }

    //derivatives

    /**
     * List all derivative tickers
     * See: /derivatives
     *
     * @param include_tickers Which tickers to show
     * @return List all derivative tickers
     */
    response derivative_tickers(includes include_tickers = unexpired) {
        std::string request = "/api/v3/derivatives?";

        request += "&include_tickers=" + _to_str(include_tickers);

        return geckoRequest(request);
    }

    /**
     * List all derivative exchanges
     * See: /derivatives/exchanges
     *
     * @param order Sort results by field
     * @param per_page Total results per page {1 - 250}
     * @param page Results page
     * @return List all derivative exchanges
     */
    response derivative_exchanges(derivative_order order, int per_page = 100, int page = 1) {
        std::string request = "/api/v3/derivatives/exchanges?";

        request += "&order=" + _to_str(order);
        request += "&per_page=" + std::to_string(per_page);
        request += "&page=" + std::to_string(page);

        return geckoRequest(request);
    }

    /**
     * Show derivative exchange data
     * See: /derivatives/exchanges/{id}
     *
     * @param derivExchangeID Derivative exchange ID, from coingecko::derivative_exchanges
     * @param include_tickers Which tickers to show
     * @return show derivative exchange data
     */
    response derivative_exchange_data(const std::string& derivExchangeID, includes include_tickers = unexpired) {
        std::string request = "/api/v3/derivatives/exchanges/" + derivExchangeID + "?";

        request += "&include_tickers=" + _to_str(include_tickers);

        return geckoRequest(request);
    }

    /**
     * List ll derivative exchanges name and identifier
     * See: /derivatives/exchanges/list
     *
     * @return List all derivative exchanges name and identifier
     */
    response derivative_exchanges_names() {
        std::string request = "/api/v3/derivatives/exchanges/list";

        return geckoRequest(request);
    }

    //status updates

    /**
     * List all status updates with data
     * See: /status_updates
     *
     * @param category Category to filter with
     * @param projectType Project type
     * @param per_page Total results per page {1 - 250}
     * @param page Results page
     * @return List all status_updates with data
     */
    response status_updates(status_category category, project_type project_type, int per_page, int page) {
        std::string request = "/api/v3/status_updates?";

        request += "&category=" + _to_str(category);
        request += "&project_type=" + _to_str(project_type);
        request += "&per_page=" + std::to_string(per_page);
        request += "&page=" + std::to_string(page);

        return geckoRequest(request);
    }

    //events

    /**
     * Get events, paginated by 100
     * See: /events
     *
     * @param country_code Country codes, see coingecko::event_countries
     * @param type Type of events, see coingecko::event_types
     * @param page Page of results
     * @param upcoming_events_only List only upcoming events
     * @param from_date List events after this date; yyyy-mm-dd format
     * @param to_date List events before this date; yyyy-mm-dd format
     * @return List events
     */
    response events(const std::string& country_code, const std::string& type, int page,
                    bool upcoming_events_only, const std::string& from_date, const std::string& to_date) {
        std::string request = "/api/v3/events?";

        request += "&country_code=" + country_code;
        request += "&type=" + type;
        request += "&page=" + std::to_string(page);
        request += "&upcoming_events_only=" + (upcoming_events_only?sTrue:sFalse);
        request += "&from_date=" + from_date;
        request += "&to_date=" + to_date;

        return geckoRequest(request);
    }

    /**
     * Get list of event countries
     * See: /events/countries
     *
     * @return List event countries
     */
    response event_countries() {
        std::string request = "/api/v3/events/countries";

        return geckoRequest(request);
    }

    /**
     * Get list of event types
     * See: /events/types
     *
     * @return List event types
     */
    response event_types() {
        std::string request = "/api/v3/events/types";

        return geckoRequest(request);
    }

    //exchange rates

    /**
     * Get BTC to currency exchange rates
     * See: /exchange_rates
     *
     * @return List rates
     */
    response exchange_rates() {
        std::string request = "/api/v3/exchange_rates";

        return geckoRequest(request);
    }

    //trending

    /**
     * Top 7 trending coins on coingecko as searched by users
     * See: /search/trending
     *
     * @return List trending coins by most popular first
     */
    response trending() {
        std::string request = "/api/v3/search/trending";

        return geckoRequest(request);
    }

    //global

    /**
     * Get cryptocurrency global data
     * See: /global
     *
     * @return Get global data - total_volume, total_market_cap, ongoing icos etc
     */
    response global_data() {
        std::string request = "/api/v3/global";

        return geckoRequest(request);
    }

    /**
     * Get top 100 cryptocurrency global decentralized finance data
     * See: /global/decentralized_finance_defi
     *
     * @return Get cryptocurrency global decentralized finance(defi) data
     */
    response global_defi_data() {
        std::string request = "/api/v3/global/decentralized_finance_defi";

        return geckoRequest(request);
    }
}

#endif