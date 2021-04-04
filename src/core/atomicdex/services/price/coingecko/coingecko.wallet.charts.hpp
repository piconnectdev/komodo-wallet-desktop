#pragma once

#include <array>
#include <unordered_map>

//! Deps
#include <boost/thread/synchronized_value.hpp>
#include <entt/entity/registry.hpp>
#include <nlohmann/json.hpp>
#include <taskflow/taskflow.hpp>

//! Project Headers
#include "atomicdex/config/coins.cfg.hpp"
#include "atomicdex/constants/qt.wallet.enums.hpp"

namespace atomic_dex
{
    class coingecko_wallet_charts_service final : public ag::ecs::pre_update_system<coingecko_wallet_charts_service>
    {
        //! Private typedefs
        using t_update_time_point   = std::chrono::high_resolution_clock::time_point;
        using t_array_chart_data    = nlohmann::json;
        using t_chart_data_registry = boost::synchronized_value<std::unordered_map<std::string, t_array_chart_data>>;
        using t_fiat_data_registry  = boost::synchronized_value<t_array_chart_data>;

        //! Private member functions
        ag::ecs::system_manager& m_system_manager;
        t_update_time_point      m_update_clock;
        t_chart_data_registry    m_chart_data_registry;
        t_fiat_data_registry     m_fiat_data_registry;
        tf::Executor             m_executor;
        tf::Taskflow             m_taskflow;
        std::atomic_bool         m_is_busy{false};

        //! Private member functions
        void fetch_data_of_single_coin(const coin_config& cfg);
        void fetch_all_charts_data();
        void generate_fiat_chart();

      public:
        //! Constructor
        coingecko_wallet_charts_service(entt::registry& registry, ag::ecs::system_manager& system_manager);

        //! Destructor
        ~coingecko_wallet_charts_service() final;

        //! Override ag::system functions
        void update() final;

        void manual_refresh();

        [[nodiscard]] bool is_busy() const;
    };
} // namespace atomic_dex

REFL_AUTO(type(atomic_dex::coingecko_wallet_charts_service))