/******************************************************************************
 * Copyright © 2013-2019 The Komodo Platform Developers.                      *
 *                                                                            *
 * See the AUTHORS, DEVELOPER-AGREEMENT and LICENSE files at                  *
 * the top-level directory of this distribution for the individual copyright  *
 * holder information and the developer policies on copyright and licensing.  *
 *                                                                            *
 * Unless otherwise agreed in a custom licensing agreement, no part of the    *
 * Komodo Platform software, including this file may be copied, modified,     *
 * propagated or distributed except according to the terms contained in the   *
 * LICENSE file                                                               *
 *                                                                            *
 * Removal or modification of this copyright notice is prohibited.            *
 *                                                                            *
 ******************************************************************************/

//! Deps
#include <nlohmann/json.hpp>

//! Project Headers
#include "atomicdex/config/wallet.cfg.hpp"

namespace atomic_dex
{
    void
    from_json(const nlohmann::json& j, wallet_cfg& cfg)
    {
        j.at("name").get_to(cfg.name);
        if (j.contains("protection_pass"))
        {
            j.at("protection_pass").get_to(cfg.protection_pass);
        }
        if (j.contains("addressbook_contacts"))
        {
            for (const auto& cur: j.at("addressbook_contacts"))
            {
                addressbook_contact current_contact;
                cur.at("name").get_to(current_contact.name);
                for (const auto& cur_wallet: cur.at("wallets_info"))
                {
                    addressbook_contact_wallet_info wallet_info;
                    cur_wallet.at("type").get_to(wallet_info.type);
                    cur_wallet.at("addresses").get_to(wallet_info.addresses);
                    current_contact.wallets_info.emplace_back(std::move(wallet_info));
                }
                cfg.addressbook_contacts.emplace_back(std::move(current_contact));
            }
        }
        if (j.contains("transactions_details"))
        {
            cfg.transactions_details = j.at("transactions_details").get<decltype(cfg.transactions_details)::value_type>();
        }
    }

    void
    to_json(nlohmann::json& j, const addressbook_contact_wallet_info& cfg)
    {
        j["type"]      = cfg.type;
        j["addresses"] = cfg.addresses;
    }

    void
    to_json(nlohmann::json& j, const addressbook_contact& cfg)
    {
        j["name"]         = cfg.name;
        j["wallets_info"] = cfg.wallets_info;
        j["categories"]   = cfg.categories;
    }

    void
    to_json(nlohmann::json& j, const wallet_cfg& cfg)
    {
        j["name"]                 = cfg.name;
        j["protection_pass"]      = cfg.protection_pass;
        j["addressbook_contacts"] = cfg.addressbook_contacts;
        j["transactions_details"] = cfg.transactions_details.get();
    }

    void
    to_json(nlohmann::json& j, const transactions_contents& cfg)
    {
        j["note"]     = cfg.note;
        j["category"] = cfg.category;
    }

    void
    from_json(const nlohmann::json& j, transactions_contents& cfg)
    {
        j.at("note").get_to(cfg.note);
        j.at("category").get_to(cfg.category);
    }
} // namespace atomic_dex
