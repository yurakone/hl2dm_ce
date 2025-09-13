// server_motd.cpp (новый файл в серверной части)
#include "cbase.h"
#include "player.h"
#include "igameevents.h"
#include <windows.h>
#include <wincrypt.h>
#include <string>
#include <sstream>
#include <iomanip>
#include "hl2mp/hl2mp_player.h"
#include <viewport_panel_names.h>
#include "cbase.h"
#include "hl2mp_player.h"
#include <iostream>
#include <thread>
#include <chrono>
//#include <thirdparty/json.hpp>  
//#include <websocketpp/config/asio_no_tls_client.hpp>
//#include <websocketpp/client.hpp>
#include "tier0/memdbgon.h"

static const char* g_pszSecretKey = "my_super_secret"; // лучше вынести в cfg

//typedef websocketpp::client<websocketpp::config::asio_client> ws_client;

//static ws_client client;
//static websocketpp::connection_hdl hdl;
static bool connected = false;


#define MOTDPANEL_TYPE_URL 2
// Утилита для генерации HMAC-SHA1 токена с использованием Windows CryptoAPI
std::string GenerateToken(const std::string& sid, const std::string& pid)
{
    std::string data = sid + ":" + pid + ":" + g_pszSecretKey;

    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    std::string hex;

    if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
        return "";

    if (!CryptCreateHash(hProv, CALG_SHA1, 0, 0, &hHash))
    {
        CryptReleaseContext(hProv, 0);
        return "";
    }

    CryptHashData(hHash, (BYTE*)data.c_str(), (DWORD)data.size(), 0);

    BYTE hash[20];
    DWORD hashLen = sizeof(hash);
    if (CryptGetHashParam(hHash, HP_HASHVAL, hash, &hashLen, 0))
    {
        std::ostringstream oss;
        for (DWORD i = 0; i < hashLen; ++i)
            oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
        hex = oss.str();
    }

    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);

    return hex;
}

static void ShowCustomMOTD(CHL2MP_Player* pPlayer)
{
    if (!pPlayer) return;

    uint64 steamId = pPlayer->GetSteamIDAsUInt64();
    uint64 serverId = 0;

    // Get the server SteamID as a string
    const CSteamID* pServerSteamID = engine->GetGameServerSteamID();
    char serverSteamIDStr[32] = {0};
    if (pServerSteamID)
    {
        // Convert CSteamID to uint64 and then to string
        serverId = pServerSteamID->ConvertToUint64();
        snprintf(serverSteamIDStr, sizeof(serverSteamIDStr), "%llu", serverId);
    }
    else
    {
        // Fallback: use 0 or some other identifier
        serverId = 0;
        snprintf(serverSteamIDStr, sizeof(serverSteamIDStr), "0");
    }

    std::string sid = std::to_string(serverId);
    std::string pid = std::to_string(steamId);

    std::string token = GenerateToken(sid, pid);

    // Ссылка на твоё веб-приложение
    std::string url = "http://192.168.1.201:3000/?sid=" + sid + "&pid=" + pid + "&token=" + token;

    // Показываем MOTD
    KeyValues* data = new KeyValues("data");
    data->SetString("title", "Server Menu");
    data->SetString("msg", url.c_str());
    data->SetInt("type", MOTDPANEL_TYPE_URL);

    pPlayer->ShowViewPortPanel("info", true, data);
    data->deleteThis();
}
/*
void OnMessage(ws_client* c, websocketpp::connection_hdl hdl, ws_client::message_ptr msg) 
{
    try {
        auto json = nlohmann::json::parse(msg->get_payload());
        std::string cmd = json["cmd"];
        uint64 pid = json["pid"];

        for (int i = 1; i <= gpGlobals->maxClients; i++) {
            CHL2MP_Player* pPlayer = ToHL2MPPlayer(UTIL_PlayerByIndex(i));
            if (!pPlayer) continue;

            if (pPlayer->GetSteamIDAsUInt64() == pid) {
                if (cmd == "joingame") {
                    ClientCommand(pPlayer->edict(), "joinclass");
                }
                else if (cmd == "spectate") {
                    ClientCommand(pPlayer->edict(), "spectate");
                }
            }
        }
    }
    catch (...) {
        Warning("WS parse error\n");
    }
}


void InitWebSocket() 
{
    client.init_asio();

    client.set_open_handler([&](websocketpp::connection_hdl h) {
        hdl = h;
        connected = true;
        Msg("WebSocket connected to backend\n");
        });

    client.set_message_handler(&OnMessage);

    websocketpp::lib::error_code ec;
    ws_client::connection_ptr con = client.get_connection("ws://127.0.0.1:8081", ec);
    client.connect(con);

    std::thread([&]() { client.run(); }).detach();
}
*/
