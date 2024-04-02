/**
 * WiFiManager.h
 * 
 * WiFiManager, a library for the ESP8266/Arduino platform
 * for configuration of WiFi credentials using a Captive Portal
 * 
 * @author Creator tzapu
 * @author tablatronix
 * @version 0.0.0
 * @license MIT
 */


#ifndef WiFiManager_h
#define WiFiManager_h


/*
#if defined(ESP8266) || defined(ESP32)

#ifdef ESP8266
#include <core_version.h>
#endif

#include <vector>

// #define WM_MDNS            // includes MDNS, also set MDNS with sethostname
// #define WM_FIXERASECONFIG  // use erase flash fix
// #define WM_ERASE_NVS       // esp32 erase(true) will erase NVS 
// #define WM_RTC             // esp32 info page will include reset reasons

// #define WM_JSTEST                      // build flag for enabling js xhr tests
// #define WIFI_MANAGER_OVERRIDE_STRINGS // build flag for using own strings include

#ifdef ARDUINO_ESP8266_RELEASE_2_3_0
#warning "ARDUINO_ESP8266_RELEASE_2_3_0, some WM features disabled" 
// @todo check failing on platform = espressif8266@1.7.3
#define WM_NOASYNC         // esp8266 no async scan wifi
#define WM_NOCOUNTRY       // esp8266 no country
#define WM_NOAUTH          // no httpauth
#define WM_NOSOFTAPSSID    // no softapssid() @todo shim
#endif

// #ifdef CONFIG_IDF_TARGET_ESP32S2
// #warning ESP32S2
// #endif

// #ifdef CONFIG_IDF_TARGET_ESP32C3
// #warning ESP32C3
// #endif

// #ifdef CONFIG_IDF_TARGET_ESP32S3
// #warning ESP32S3
// #endif

#if defined(ARDUINO_ESP32S3_DEV) || defined(CONFIG_IDF_TARGET_ESP32S3)
#warning "WM_NOTEMP"
#define WM_NOTEMP // disabled temp sensor, have to determine which chip we are on
#endif

// #include "soc/efuse_reg.h" // include to add efuse chip rev to info, getChipRevision() is almost always the same though, so not sure why it matters.

// #define esp32autoreconnect    // implement esp32 autoreconnect event listener kludge, @DEPRECATED
// autoreconnect is WORKING https://github.com/espressif/arduino-esp32/issues/653#issuecomment-405604766

#define WM_WEBSERVERSHIM      // use webserver shim lib

#define WM_G(string_literal)  (String(FPSTR(string_literal)).c_str())

#ifdef ESP8266

    extern "C" {
      #include "user_interface.h"
    }
    #include <ESP8266WiFi.h>
    #include <ESP8266WebServer.h>

    #ifdef WM_MDNS
        #include <ESP8266mDNS.h>
    #endif

    #define WIFI_getChipId() ESP.getChipId() 
    #define WM_WIFIOPEN   ENC_TYPE_NONE

#elif defined(ESP32)

    #include <WiFi.h>
    #include <esp_wifi.h>  
    #include <Update.h>
    
    #define WIFI_getChipId() (uint32_t)ESP.getEfuseMac()
    #define WM_WIFIOPEN   WIFI_AUTH_OPEN

    #ifndef WEBSERVER_H
        #ifdef WM_WEBSERVERSHIM
            #include <WebServer.h>
        #else
            #include <ESP8266WebServer.h>
            // Forthcoming official ? probably never happening
            // https://github.com/esp8266/ESPWebServer
        #endif
    #endif

    #ifdef WM_ERASE_NVS
       #include <nvs.h>
       #include <nvs_flash.h>
    #endif

    #ifdef WM_MDNS
        #include <ESPmDNS.h>
    #endif

    #ifdef WM_RTC
        #ifdef ESP_IDF_VERSION_MAJOR // IDF 4+
        #if CONFIG_IDF_TARGET_ESP32 // ESP32/PICO-D4
        #include "esp32/rom/rtc.h"
        #elif CONFIG_IDF_TARGET_ESP32S2
        #include "esp32s2/rom/rtc.h"
        #elif CONFIG_IDF_TARGET_ESP32C3
        #include "esp32c3/rom/rtc.h"
        #elif CONFIG_IDF_TARGET_ESP32S3
        #include "esp32s3/rom/rtc.h"
        #else
        #error Target CONFIG_IDF_TARGET is not supported
        #endif
        #else // ESP32 Before IDF 4.0
        #include "rom/rtc.h"
        #endif
    #endif

#else
#endif

#include <DNSServer.h>
#include <memory>
*/

////////////////////////////////////////////////////
#define WM_WEBSERVERSHIM      // use webserver shim lib

#define WM_G(string_literal)  (String(FPSTR(string_literal)).c_str())


#if !( defined(ESP8266) ||  defined(ESP32) )
  #error This code is intended to run on the ESP8266 or ESP32 platform! Please check your Tools->Board setting.
#elif ( ARDUINO_ESP32S2_DEV || ARDUINO_FEATHERS2 || ARDUINO_ESP32S2_THING_PLUS || ARDUINO_MICROS2 || \
        ARDUINO_METRO_ESP32S2 || ARDUINO_MAGTAG29_ESP32S2 || ARDUINO_FUNHOUSE_ESP32S2 || \
        ARDUINO_ADAFRUIT_FEATHER_ESP32S2_NOPSRAM )
  #if (_ESPASYNC_WIFIMGR_LOGLEVEL_ > 3)
    #warning Using ESP32_S2. To follow library instructions to install esp32-s2 core and WebServer Patch
    #warning You have to select HUGE APP or 1.9-2.0 MB APP to be able to run Config Portal. Must use PSRAM
  #endif
  
  #define USING_ESP32_S2        true
  
#elif ( ARDUINO_ESP32C3_DEV )
  #if (_ESPASYNC_WIFIMGR_LOGLEVEL_ > 3)
    #if ( defined(ESP_ARDUINO_VERSION_MAJOR) && (ESP_ARDUINO_VERSION_MAJOR >= 2) )
      #warning Using ESP32_C3 using core v2.0.0+. Either LittleFS, SPIFFS or EEPROM OK
    #else
      #warning Using ESP32_C3 using core v1.0.6-. To follow library instructions to install esp32-c3 core. Only SPIFFS and EEPROM OK
    #endif
    
    #warning You have to select Flash size 2MB and Minimal APP (1.3MB + 700KB) for some boards
  
  #endif
  
  #define USING_ESP32_C3        true
  
#elif ( defined(ARDUINO_ESP32S3_DEV) || defined(ARDUINO_ESP32_S3_BOX) || defined(ARDUINO_TINYS3) || \
        defined(ARDUINO_PROS3) || defined(ARDUINO_FEATHERS3) )

  #if (_ESPASYNC_WIFIMGR_LOGLEVEL_ > 3)    
    #warning Using ESP32_S3. To install esp32-s3-support branch if using core v2.0.2-
  #endif
  
  #define USING_ESP32_S3        true   
#endif

////////////////////////////////////////////////////

#define ESP_ASYNC_WIFIMANAGER_VERSION           "ESPAsync_WiFiManager v1.15.1"

#define ESP_ASYNC_WIFIMANAGER_VERSION_MAJOR     1
#define ESP_ASYNC_WIFIMANAGER_VERSION_MINOR     15
#define ESP_ASYNC_WIFIMANAGER_VERSION_PATCH     1

#define ESP_ASYNC_WIFIMANAGER_VERSION_INT       1015001

////////////////////////////////////////////////////

#if ESP8266
  #if (ARDUINO_ESP8266_GIT_VER == 0xcf6ff4c4)
    #define USING_ESP8266_CORE_VERSION    30002
    #define ESP8266_CORE_VERSION          "ESP8266 core v3.0.2"
    
    #if (_ESPASYNC_WIFIMGR_LOGLEVEL_ > 3) 
      #warning USING_ESP8266_CORE_VERSION "3.0.2"
    #endif
    
  #elif (ARDUINO_ESP8266_GIT_VER == 0xcbf44fb3)
    #define USING_ESP8266_CORE_VERSION    30001
    #define ESP8266_CORE_VERSION          "ESP8266 core v3.0.1"
    
    #if (_ESPASYNC_WIFIMGR_LOGLEVEL_ > 3) 
      #warning USING_ESP8266_CORE_VERSION "3.0.1"
    #endif
    
  #elif (ARDUINO_ESP8266_GIT_VER == 0xefb0341a)
    #define USING_ESP8266_CORE_VERSION    30000
    #define ESP8266_CORE_VERSION          "ESP8266 core v3.0.0"
    
    #if (_ESPASYNC_WIFIMGR_LOGLEVEL_ > 3) 
      #warning USING_ESP8266_CORE_VERSION "3.0.0"
    #endif
    
  #elif (ARDUINO_ESP8266_GIT_VER == 0x2843a5ac)
    #define USING_ESP8266_CORE_VERSION    20704
    #define ESP8266_CORE_VERSION          "ESP8266 core v2.7.4"
    
    #if (_ESPASYNC_WIFIMGR_LOGLEVEL_ > 3) 
      #warning USING_ESP8266_CORE_VERSION "2.7.4"
    #endif
    
  #elif (ARDUINO_ESP8266_GIT_VER == 0x5d3af165)
    #define USING_ESP8266_CORE_VERSION    20703
    #define ESP8266_CORE_VERSION          "ESP8266 core v2.7.3"
    
    #if (_ESPASYNC_WIFIMGR_LOGLEVEL_ > 3) 
      #warning USING_ESP8266_CORE_VERSION "2.7.3"
    #endif
    
  #elif (ARDUINO_ESP8266_GIT_VER == 0x39c79d9b)
    #define USING_ESP8266_CORE_VERSION    20702
    #define ESP8266_CORE_VERSION          "ESP8266 core v2.7.2"
    
    #if (_ESPASYNC_WIFIMGR_LOGLEVEL_ > 3)
      #warning USING_ESP8266_CORE_VERSION "2.7.2"
    #endif
    
  #elif (ARDUINO_ESP8266_GIT_VER == 0xa5432625)
    #define USING_ESP8266_CORE_VERSION    20701
    #define ESP8266_CORE_VERSION          "ESP8266 core v2.7.1"
    
    #if (_ESPASYNC_WIFIMGR_LOGLEVEL_ > 3) 
      #warning USING_ESP8266_CORE_VERSION "2.7.1"
    #endif
    
  #elif (ARDUINO_ESP8266_GIT_VER == 0x3d128e5c)
    #define USING_ESP8266_CORE_VERSION    20603
    #define ESP8266_CORE_VERSION          "ESP8266 core v2.6.3"
    
    #if (_ESPASYNC_WIFIMGR_LOGLEVEL_ > 3) 
      #warning USING_ESP8266_CORE_VERSION "2.6.3"
    #endif
    
  #elif (ARDUINO_ESP8266_GIT_VER == 0x482516e3)
    #define USING_ESP8266_CORE_VERSION    20602
    #define ESP8266_CORE_VERSION          "ESP8266 core v2.6.2"
    
    #if (_ESPASYNC_WIFIMGR_LOGLEVEL_ > 3) 
      #warning USING_ESP8266_CORE_VERSION "2.6.2"
    #endif
    
  #elif (ARDUINO_ESP8266_GIT_VER == 0x482516e3)
    #define USING_ESP8266_CORE_VERSION    20601
    #define ESP8266_CORE_VERSION          "ESP8266 core v2.6.1"
    
    #if (_ESPASYNC_WIFIMGR_LOGLEVEL_ > 3) 
      #warning USING_ESP8266_CORE_VERSION "2.6.1"
    #endif
    
  #elif (ARDUINO_ESP8266_GIT_VER == 0x643ec203)
    #define USING_ESP8266_CORE_VERSION    20600
    #define ESP8266_CORE_VERSION          "ESP8266 core v2.6.0"
    
    #if (_ESPASYNC_WIFIMGR_LOGLEVEL_ > 3) 
      #warning USING_ESP8266_CORE_VERSION "2.6.0"
    #endif
    
  #elif (ARDUINO_ESP8266_GIT_VER == 0x8b899c12)
    #define USING_ESP8266_CORE_VERSION    20502
    #define ESP8266_CORE_VERSION          "ESP8266 core v2.5.2"
    
    #if (_ESPASYNC_WIFIMGR_LOGLEVEL_ > 3) 
      #warning USING_ESP8266_CORE_VERSION "2.5.2"
    #endif
    
  #elif (ARDUINO_ESP8266_GIT_VER == 0x00000000)
    #define USING_ESP8266_CORE_VERSION    20402
    #define ESP8266_CORE_VERSION          "ESP8266 core v2.4.2"
    
    #if (_ESPASYNC_WIFIMGR_LOGLEVEL_ > 3) 
      #warning USING_ESP8266_CORE_VERSION "2.4.2"
    #endif
    
  #elif (ARDUINO_ESP8266_GIT_VER == 0x643ec203)
    #define USING_ESP8266_CORE_VERSION    0
    #define ESP8266_CORE_VERSION          "ESP8266 core too old"
    #warning USING_ESP8266_CORE_VERSION "0.0.0"
  #else
    #define USING_ESP8266_CORE_VERSION    999999
    #define ESP8266_CORE_VERSION          "ESP8266 core unknown"
    #warning USING_ESP8266_CORE_VERSION "x.y.z"  
  #endif
#endif

////////////////////////////////////////////////////
#include "Arduino.h"
#include "ESPAsync_WiFiManager_Debug.h"
#include "StreamString.h"

////////////////////////////////////////////////////

//KH, for ESP32
#ifdef ESP8266
  #include <ESP8266WiFi.h>
  #include <ESPAsyncWebServer.h>
#else   //ESP32
  #include <WiFi.h>
  #include <ESPAsyncWebServer.h>
  #include <ArduinoOTA.h>
#endif

#include <ESPAsyncDNSServer.h>

#include <memory>
#undef min
#undef max

#include <algorithm>

////////////////////////////////////////////////////

// fix crash on ESP32 (see https://github.com/alanswx/ESPAsyncWiFiManager/issues/44)
#if defined(ESP8266)
  typedef int     wifi_ssid_count_t;
#else
  typedef int16_t wifi_ssid_count_t;
#endif

////////////////////////////////////////////////////

//KH, for ESP32
#ifdef ESP8266
  extern "C"
  {
    #include "user_interface.h"
  }
  
  #define ESP_getChipId()   (ESP.getChipId())
#else   //ESP32

  #include <esp_wifi.h>
  
  uint32_t getChipID();
  uint32_t getChipOUI();
   
  #if defined(ESP_getChipId)
    #undef ESP_getChipId
  #endif
  
  #define ESP_getChipId()   getChipID()
  #define WIFI_getChipId() (uint32_t)ESP.getEfuseMac()
  #define ESP_getChipOUI()  getChipOUI()
  #define WM_WIFIOPEN   WIFI_AUTH_OPEN

#endif

////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Include wm strings vars
// Pass in strings env override via WM_STRINGS_FILE
#ifndef WM_STRINGS_FILE
#define WM_STRINGS_FILE "wm_strings_en.h" // this includes constants as dependency
#endif
#include WM_STRINGS_FILE

// prep string concat vars
#define WM_STRING2(x) #x
#define WM_STRING(x) WM_STRING2(x)    

// #include <esp_idf_version.h>
#ifdef ESP_IDF_VERSION
    // #pragma message "ESP_IDF_VERSION_MAJOR = " WM_STRING(ESP_IDF_VERSION_MAJOR)
    // #pragma message "ESP_IDF_VERSION_MINOR = " WM_STRING(ESP_IDF_VERSION_MINOR)
    // #pragma message "ESP_IDF_VERSION_PATCH = " WM_STRING(ESP_IDF_VERSION_PATCH)
    #define VER_IDF_STR WM_STRING(ESP_IDF_VERSION_MAJOR)  "."  WM_STRING(ESP_IDF_VERSION_MINOR)  "."  WM_STRING(ESP_IDF_VERSION_PATCH)
#else 
    #define VER_IDF_STR "Unknown"
#endif

#ifdef Arduino_h
    #ifdef ESP32
    // #include "esp_arduino_version.h" // esp32 arduino > 2.x
    #endif
    // esp_get_idf_version
    #ifdef ESP_ARDUINO_VERSION
        // #pragma message "ESP_ARDUINO_VERSION_MAJOR = " WM_STRING(ESP_ARDUINO_VERSION_MAJOR)
        // #pragma message "ESP_ARDUINO_VERSION_MINOR = " WM_STRING(ESP_ARDUINO_VERSION_MINOR)
        // #pragma message "ESP_ARDUINO_VERSION_PATCH = " WM_STRING(ESP_ARDUINO_VERSION_PATCH)
        #ifdef ESP_ARDUINO_VERSION_MAJOR
        #define VER_ARDUINO_STR WM_STRING(ESP_ARDUINO_VERSION_MAJOR)  "."  WM_STRING(ESP_ARDUINO_VERSION_MINOR)  "."  WM_STRING(ESP_ARDUINO_VERSION_PATCH)
        #else
        #define VER_ARDUINO_STR "Unknown"
        #endif
    #else
        #include <core_version.h>
        // #pragma message "ESP_ARDUINO_VERSION_GIT  = " WM_STRING(ARDUINO_ESP32_GIT_VER)//  0x46d5afb1
        // #pragma message "ESP_ARDUINO_VERSION_DESC = " WM_STRING(ARDUINO_ESP32_GIT_DESC) //  1.0.6
        // #pragma message "ESP_ARDUINO_VERSION_REL  = " WM_STRING(ARDUINO_ESP32_RELEASE) //"1_0_6"
        #ifdef ESP_ARDUINO_VERSION_MAJOR
        #define VER_ARDUINO_STR WM_STRING(ESP_ARDUINO_VERSION_MAJOR)  "."  WM_STRING(ESP_ARDUINO_VERSION_MINOR)  "."  WM_STRING(ESP_ARDUINO_VERSION_PATCH)
        #else
        #define VER_ARDUINO_STR "Unknown"
        #endif
    #endif
#else 
#define VER_ARDUINO_STR "Unknown"
#endif

// #pragma message "VER_IDF_STR = " WM_STRING(VER_IDF_STR)
// #pragma message "VER_ARDUINO_STR = " WM_STRING(VER_ARDUINO_STR)

#ifndef WIFI_MANAGER_MAX_PARAMS
    #define WIFI_MANAGER_MAX_PARAMS 5 // params will autoincrement and realloc by this amount when max is reached
#endif

#define WFM_LABEL_BEFORE 1
#define WFM_LABEL_AFTER 2
#define WFM_NO_LABEL 0
#define WFM_LABEL_DEFAULT 1

class WiFiManagerParameter {
  public:
    /** 
        Create custom parameters that can be added to the WiFiManager setup web page
        @id is used for HTTP queries and must not contain spaces nor other special characters
    */
    WiFiManagerParameter();
    WiFiManagerParameter(const char *custom);
    WiFiManagerParameter(const char *id, const char *label);
    WiFiManagerParameter(const char *id, const char *label, const char *defaultValue, int length);
    WiFiManagerParameter(const char *id, const char *label, const char *defaultValue, int length, const char *custom);
    WiFiManagerParameter(const char *id, const char *label, const char *defaultValue, int length, const char *custom, int labelPlacement);
    ~WiFiManagerParameter();
    // WiFiManagerParameter& operator=(const WiFiManagerParameter& rhs);

    const char *getID() const;
    const char *getValue() const;
    const char *getLabel() const;
    const char *getPlaceholder() const; // @deprecated, use getLabel
    int         getValueLength() const;
    int         getLabelPlacement() const;
    virtual const char *getCustomHTML() const;
    void        setValue(const char *defaultValue, int length);

  protected:
    void init(const char *id, const char *label, const char *defaultValue, int length, const char *custom, int labelPlacement);

  private:
    WiFiManagerParameter& operator=(const WiFiManagerParameter&);
    const char *_id;
    const char *_label;
    char       *_value;
    int         _length;
    int         _labelPlacement;
  protected:
    const char *_customHTML;
    friend class WiFiManager;
};


class WiFiManager
{
  public:
    WiFiManager(Print& consolePort);
    WiFiManager();
    ~WiFiManager();
    void WiFiManagerInit();

    // auto connect to saved wifi, or custom, and start config portal on failures
    boolean       autoConnect();
    boolean       autoConnect(char const *apName, char const *apPassword = NULL);

    //manually start the config portal, autoconnect does this automatically on connect failure
    boolean       startConfigPortal(); // auto generates apname
    boolean       startConfigPortal(char const *apName, char const *apPassword = NULL);

    //manually stop the config portal if started manually, stop immediatly if non blocking, flag abort if blocking
    bool          stopConfigPortal();
    
    //manually start the web portal, autoconnect does this automatically on connect failure    
    void          startWebPortal();

    //manually stop the web portal if started manually
    void          stopWebPortal();

    // Run webserver processing, if setConfigPortalBlocking(false)
    boolean       process();

    // get the AP name of the config portal, so it can be used in the callback
    String        getConfigPortalSSID();
    int           getRSSIasQuality(int RSSI);

    // erase wifi credentials
    void          resetSettings();

    // reboot esp
    void          reboot();

    // disconnect wifi, without persistent saving or erasing
    bool          disconnect();

    // erase esp
    bool          erase();
    bool          erase(bool opt);

    //adds a custom parameter, returns false on failure
    bool          addParameter(WiFiManagerParameter *p);

    //returns the list of Parameters
    WiFiManagerParameter** getParameters();

    // returns the Parameters Count
    int           getParametersCount();

    // SET CALLBACKS

    //called after AP mode and config portal has started
    void          setAPCallback( std::function<void(WiFiManager*)> func );

    //called after webserver has started
    void          setWebServerCallback( std::function<void()> func );

    //called when settings reset have been triggered
    void          setConfigResetCallback( std::function<void()> func );

    //called when wifi settings have been changed and connection was successful ( or setBreakAfterConfig(true) )
    void          setSaveConfigCallback( std::function<void()> func );

    //called when saving params-in-wifi or params before anything else happens (eg wifi)
    void          setPreSaveConfigCallback( std::function<void()> func );

    //called when saving params before anything else happens
    void          setPreSaveParamsCallback( std::function<void()> func );

    //called when saving either params-in-wifi or params page
    void          setSaveParamsCallback( std::function<void()> func );

    //called just before doing OTA update
    void          setPreOtaUpdateCallback( std::function<void()> func );

    //called on progress doing OTA update
    void          setProgressOtaUpdateCallback(std::function<void(size_t current, size_t final)> func);

    //called after OTA update
    void          setEndOtaUpdateCallback(std::function<void(bool success)> func);

    //called when config portal is timeout
    void          setConfigPortalTimeoutCallback( std::function<void()> func );

    //sets timeout before AP,webserver loop ends and exits even if there has been no setup.
    //useful for devices that failed to connect at some point and got stuck in a webserver loop
    //in seconds setConfigPortalTimeout is a new name for setTimeout, ! not used if setConfigPortalBlocking
    void          setConfigPortalTimeout(unsigned long seconds);
    void          setTimeout(unsigned long seconds); // @deprecated, alias

    //sets timeout for which to attempt connecting, useful if you get a lot of failed connects
    void          setConnectTimeout(unsigned long seconds);

    // sets number of retries for autoconnect, force retry after wait failure exit
    void          setConnectRetries(uint8_t numRetries); // default 1
    
    //sets timeout for which to attempt connecting on saves, useful if there are bugs in esp waitforconnectloop
    void          setSaveConnectTimeout(unsigned long seconds);
    
    // lets you disable automatically connecting after save from webportal
    void          setSaveConnect(bool connect = true);
    
    // toggle debug output
    void          setDebugOutput(boolean debug);
    void          setDebugOutput(boolean debug, String prefix); // log line prefix, default "*wm:"

    //set min quality percentage to include in scan, defaults to 8% if not specified
    void          setMinimumSignalQuality(int quality = 8);
    
    //sets a custom ip /gateway /subnet configuration
    void          setAPStaticIPConfig(IPAddress ip, IPAddress gw, IPAddress sn);
    
    //sets config for a static IP
    void          setSTAStaticIPConfig(IPAddress ip, IPAddress gw, IPAddress sn);
    
    //sets config for a static IP with DNS
    void          setSTAStaticIPConfig(IPAddress ip, IPAddress gw, IPAddress sn, IPAddress dns);
    
    //if this is set, it will exit after config, even if connection is unsuccessful.
    void          setBreakAfterConfig(boolean shouldBreak);
    
    // if this is set, portal will be blocking and wait until save or exit, 
    // is false user must manually `process()` to handle config portal,
    // setConfigPortalTimeout is ignored in this mode, user is responsible for closing configportal
    void          setConfigPortalBlocking(boolean shouldBlock);
    
    //add custom html at inside <head> for all pages
    void          setCustomHeadElement(const char* html);

    //if this is set, customise style
    void          setCustomMenuHTML(const char* html);

    //if this is true, remove duplicated Access Points - defaut true
    void          setRemoveDuplicateAPs(boolean removeDuplicates);
    
    //setter for ESP wifi.persistent so we can remember it and restore user preference, as WIFi._persistent is protected
    void          setRestorePersistent(boolean persistent);
    
    //if true, always show static net inputs, IP, subnet, gateway, else only show if set via setSTAStaticIPConfig
    void          setShowStaticFields(boolean alwaysShow);
    
    //if true, always show static dns, esle only show if set via setSTAStaticIPConfig
    void          setShowDnsFields(boolean alwaysShow);
    
    // toggle showing the saved wifi password in wifi form, could be a security issue.
    void          setShowPassword(boolean show);
    
    //if false, disable captive portal redirection
    void          setCaptivePortalEnable(boolean enabled);
    
    //if false, timeout captive portal even if a STA client connected to softAP (false), suggest disabling if captiveportal is open
    void          setAPClientCheck(boolean enabled);
    
    //if true, reset timeout when webclient connects (true), suggest disabling if captiveportal is open    
    void          setWebPortalClientCheck(boolean enabled);
    
    // if true, enable autoreconnecting
    void          setWiFiAutoReconnect(boolean enabled);
    
    // if true, wifiscan will show percentage instead of quality icons, until we have better templating
    void          setScanDispPerc(boolean enabled);
    
    // if true (default) then start the config portal from autoConnect if connection failed
    void          setEnableConfigPortal(boolean enable);

    // if true (default) then stop the config portal from autoConnect when wifi is saved
    void          setDisableConfigPortal(boolean enable);

    // set a custom hostname, sets sta and ap dhcp client id for esp32, and sta for esp8266
    bool          setHostname(const char * hostname);
    bool          setHostname(String hostname);

    // show erase wifi onfig button on info page, true
    void          setShowInfoErase(boolean enabled);

    // show OTA upload button on info page
    void          setShowInfoUpdate(boolean enabled);

    // set ap channel
    void          setWiFiAPChannel(int32_t channel);
    
    // set ap hidden
    void          setWiFiAPHidden(bool hidden); // default false
    
    // clean connect, always disconnect before connecting
    void          setCleanConnect(bool enable); // default false

    // set custom menu items and order, vector or arr
    // see _menutokens for ids
    void          setMenu(std::vector<const char*>& menu);
    void          setMenu(const char* menu[], uint8_t size);
    
    // set the webapp title, default WiFiManager
    void          setTitle(String title);

    // add params to its own menu page and remove from wifi, NOT TO BE COMBINED WITH setMenu!
    void          setParamsPage(bool enable);

    // get last connection result, includes autoconnect and wifisave
    uint8_t       getLastConxResult();
    
    // get a status as string
    String        getWLStatusString(uint8_t status);    
    String        getWLStatusString();    

    // get wifi mode as string
    String        getModeString(uint8_t mode);

    // check if the module has a saved ap to connect to
    bool          getWiFiIsSaved();

    // helper to get saved password, if persistent get stored, else get current if connected    
    String        getWiFiPass(bool persistent = true);

    // helper to get saved ssid, if persistent get stored, else get current if connected
    String        getWiFiSSID(bool persistent = true);

    // debug output the softap config
    void          debugSoftAPConfig();

    // debug output platform info and versioning
    void          debugPlatformInfo();

    // helper for html
    String        htmlEntities(String str, bool whitespace = false);
    
    // set the country code for wifi settings, CN
    void          setCountry(String cc);

    // set body class (invert), may be used for hacking in alt classes
    void          setClass(String str);

    // set dark mode via invert class
    void          setDarkMode(bool enable);

    // get default ap esp uses , esp_chipid etc
    String        getDefaultAPName();
    
    // set port of webserver, 80
    void          setHttpPort(uint16_t port);

    // check if config portal is active (true)
    bool          getConfigPortalActive();
    
    // check if web portal is active (true)
    bool          getWebPortalActive();

    // to preload autoconnect for test fixtures or other uses that skip esp sta config
    bool          preloadWiFi(String ssid, String pass);

    // get hostname helper
    String        getWiFiHostname();


//    std::unique_ptr<DNSServer>        dnsServer;
    std::unique_ptr<AsyncDNSServer>        dnsServer;

    #if defined(ESP32) && defined(WM_WEBSERVERSHIM)
        using WM_WebServer = AsyncWebServer;
    #else
        using WM_WebServer = AsyncWebServer;
    #endif
    
    std::unique_ptr<WM_WebServer> server;

  private:
    // vars
    std::vector<uint8_t> _menuIds;
    std::vector<const char *> _menuIdsParams  = {"wifi","param","info","exit"};
    std::vector<const char *> _menuIdsUpdate  = {"wifi","param","info","update","exit"};
    std::vector<const char *> _menuIdsDefault = {"wifi","info","exit","sep","update"};

    // ip configs @todo struct ?
    IPAddress     _ap_static_ip;
    IPAddress     _ap_static_gw;
    IPAddress     _ap_static_sn;
    IPAddress     _sta_static_ip;
    IPAddress     _sta_static_gw;
    IPAddress     _sta_static_sn;
    IPAddress     _sta_static_dns;

    unsigned long _configPortalStart      = 0; // ms config portal start time (updated for timeouts)
    unsigned long _webPortalAccessed      = 0; // ms last web access time
    uint8_t       _lastconxresult         = WL_IDLE_STATUS; // store last result when doing connect operations
    int           _numNetworks            = 0; // init index for numnetworks wifiscans
    unsigned long _lastscan               = 0; // ms for timing wifi scans
    unsigned long _startscan              = 0; // ms for timing wifi scans
    unsigned long _startconn              = 0; // ms for timing wifi connects
    // OTA
    String _update_error = "";
    unsigned long _current_progress_size;


    // defaults
    const byte    DNS_PORT                = 53;
    String        _apName                 = "no-net";
    String        _apPassword             = "";
    String        _ssid                   = ""; // var temp ssid
    String        _pass                   = ""; // var temp psk
    String        _defaultssid            = ""; // preload ssid
    String        _defaultpass            = ""; // preload pass

    // options flags
    unsigned long _configPortalTimeout    = 0; // ms close config portal loop if set (depending on  _cp/webClientCheck options)
    unsigned long _connectTimeout         = 0; // ms stop trying to connect to ap if set
    unsigned long _saveTimeout            = 0; // ms stop trying to connect to ap on saves, in case bugs in esp waitforconnectresult
    
    WiFiMode_t    _usermode               = WIFI_STA; // Default user mode
    String        _wifissidprefix         = FPSTR(S_ssidpre); // auto apname prefix prefix+chipid
    int           _cpclosedelay           = 2000; // delay before wifisave, prevents captive portal from closing to fast.
    bool          _cleanConnect           = false; // disconnect before connect in connectwifi, increases stability on connects
    bool          _connectonsave          = true; // connect to wifi when saving creds
    bool          _disableSTA             = false; // disable sta when starting ap, always
    bool          _disableSTAConn         = true;  // disable sta when starting ap, if sta is not connected ( stability )
    bool          _channelSync            = false; // use same wifi sta channel when starting ap
    int32_t       _apChannel              = 0; // default channel to use for ap, 0 for auto
    bool          _apHidden               = false; // store softap hidden value
    uint16_t      _httpPort               = 80; // port for webserver
    // uint8_t       _retryCount             = 0; // counter for retries, probably not needed if synchronous
    uint8_t       _connectRetries         = 1; // number of sta connect retries, force reconnect, wait loop (connectimeout) does not always work and first disconnect bails
    bool          _aggresiveReconn        = true; // use an agrressive reconnect strategy, WILL delay conxs
                                                   // on some conn failure modes will add delays and many retries to work around esp and ap bugs, ie, anti de-auth protections
                                                   // https://github.com/tzapu/WiFiManager/issues/1067
    bool          _allowExit              = true; // allow exit in nonblocking, else user exit/abort calls will be ignored including cptimeout

    #ifdef ESP32
    wifi_event_id_t wm_event_id           = 0;
    static uint8_t _lastconxresulttmp; // tmp var for esp32 callback
    #endif

    #ifndef WL_STATION_WRONG_PASSWORD
    uint8_t WL_STATION_WRONG_PASSWORD     = 7; // @kludge define a WL status for wrong password
    #endif

    // parameter options
    int           _minimumQuality         = -1;    // filter wifiscan ap by this rssi
    int           _staShowStaticFields    = 0;     // ternary 1=always show static ip fields, 0=only if set, -1=never(cannot change ips via web!)
    int           _staShowDns             = 0;     // ternary 1=always show dns, 0=only if set, -1=never(cannot change dns via web!)
    boolean       _removeDuplicateAPs     = true;  // remove dup aps from wifiscan
    boolean       _showPassword           = false; // show or hide saved password on wifi form, might be a security issue!
    boolean       _shouldBreakAfterConfig = false; // stop configportal on save failure
    boolean       _configPortalIsBlocking = true;  // configportal enters blocking loop 
    boolean       _enableCaptivePortal    = true;  // enable captive portal redirection
    boolean       _userpersistent         = true;  // users preffered persistence to restore
    boolean       _wifiAutoReconnect      = true;  // there is no platform getter for this, we must assume its true and make it so
    boolean       _apClientCheck          = false; // keep cp alive if ap have station
    boolean       _webClientCheck         = true;  // keep cp alive if web have client
    boolean       _scanDispOptions        = false; // show percentage in scans not icons
    boolean       _paramsInWifi           = true;  // show custom parameters on wifi page
    boolean       _showInfoErase          = true;  // info page erase button
    boolean       _showInfoUpdate         = true;  // info page update button
    boolean       _showBack               = false; // show back button
    boolean       _enableConfigPortal     = true;  // FOR autoconnect - start config portal if autoconnect failed
    boolean       _disableConfigPortal    = true;  // FOR autoconnect - stop config portal if cp wifi save
    String        _hostname               = "";    // hostname for esp8266 for dhcp, and or MDNS

    const char*   _customHeadElement      = ""; // store custom head element html from user isnide <head>
    const char*   _customMenuHTML         = ""; // store custom head element html from user inside <>
    String        _bodyClass              = ""; // class to add to body
    String        _title                  = FPSTR(S_brand); // app title -  default WiFiManager

    // internal options
    
    // wifiscan notes
    // currently disabled due to issues with caching, sometimes first scan is empty esp32 wifi not init yet race, or portals hit server nonstop flood
    // The following are background wifi scanning optimizations
    // experimental to make scans faster, preload scans after starting cp, and visiting home page, so when you click wifi its already has your list
    // ideally we would add async and xhr here but I am holding off on js requirements atm
    // might be slightly buggy since captive portals hammer the home page, @todo workaround this somehow.
    // cache time helps throttle this
    // async enables asyncronous scans, so they do not block anything
    // the refresh button bypasses cache
    // no aps found is problematic as scans are always going to want to run, leading to page load delays
    // 
    // These settings really only make sense with _preloadwifiscan true
    // but not limited to, we could run continuous background scans on various page hits, or xhr hits
    // which would be better coupled with asyncscan
    // atm preload is only done on root hit and startcp
    boolean       _preloadwifiscan        = true; // preload wifiscan if true
    unsigned int  _scancachetime          = 30000; // ms cache time for preload scans
    boolean       _asyncScan              = true; // perform wifi network scan async

    boolean       _autoforcerescan        = false;  // automatically force rescan if scan networks is 0, ignoring cache
    
    boolean       _disableIpFields        = false; // modify function of setShow_X_Fields(false), forces ip fields off instead of default show if set, eg. _staShowStaticFields=-1

    String        _wificountry            = "";  // country code, @todo define in strings lang

    // wrapper functions for handling setting and unsetting persistent for now.
    bool          esp32persistent         = false;
    bool          _hasBegun               = false; // flag wm loaded,unloaded
    void          _begin();
    void          _end();

    void          setupConfigPortal();
    bool          shutdownConfigPortal();
    bool          setupHostname(bool restart);
    
#ifdef NO_EXTRA_4K_HEAP
    boolean       _tryWPS                 = false; // try WPS on save failure, unsupported
    void          startWPS();
#endif

    bool          startAP();
    void          setupDNSD();
    void          setupHTTPServer();

    uint8_t       connectWifi(String ssid, String pass, bool connect = true);
    bool          setSTAConfig();
    bool          wifiConnectDefault();
    bool          wifiConnectNew(String ssid, String pass,bool connect = true);

    uint8_t       waitForConnectResult();
    uint8_t       waitForConnectResult(uint32_t timeout);
    void          updateConxResult(uint8_t status);

    // webserver handlers
    void          HTTPSend(AsyncWebServerRequest *request, const String &content);
    void          handleRoot(AsyncWebServerRequest *request);
    void          handleWifi(AsyncWebServerRequest *request, boolean scan);
    void          handleWifiSave(AsyncWebServerRequest *request);
    void          handleInfo(AsyncWebServerRequest *request);
    void          handleReset(AsyncWebServerRequest *request);
    void          handleNotFound(AsyncWebServerRequest *request);
    void          handleExit(AsyncWebServerRequest *request);
    void          handleClose(AsyncWebServerRequest *request);
    // void          handleErase();
    void          handleErase(AsyncWebServerRequest *request, boolean opt);
    void          handleParam(AsyncWebServerRequest *request);
    void          handleWiFiStatus(AsyncWebServerRequest *request);
    void          handleRequest(AsyncWebServerRequest *request);
    void          handleParamSave(AsyncWebServerRequest *request);
    void          doParamSave(AsyncWebServerRequest *request);

    boolean       captivePortal(AsyncWebServerRequest *request);
    boolean       configPortalHasTimeout();
    uint8_t       processConfigPortal();
    void          stopCaptivePortal();
	// OTA Update handler
	void          handleUpdate(AsyncWebServerRequest *request);
	void          handleUpdating(AsyncWebServerRequest *request, const String& filename, size_t index, uint8_t *data, size_t len, bool final);


    // wifi platform abstractions
    bool          WiFi_Mode(WiFiMode_t m);
    bool          WiFi_Mode(WiFiMode_t m,bool persistent);
    bool          WiFi_Disconnect();
    bool          WiFi_enableSTA(bool enable);
    bool          WiFi_enableSTA(bool enable,bool persistent);
    bool          WiFi_eraseConfig();
    uint8_t       WiFi_softap_num_stations();
    bool          WiFi_hasAutoConnect();
    void          WiFi_autoReconnect();
    String        WiFi_SSID(bool persistent = true) const;
    String        WiFi_psk(bool persistent = true) const;
    bool          WiFi_scanNetworks();
    bool          WiFi_scanNetworks(bool force,bool async);
    bool          WiFi_scanNetworks(unsigned int cachetime,bool async);
    bool          WiFi_scanNetworks(unsigned int cachetime);
    void          WiFi_scanComplete(int networksFound);
    bool          WiFiSetCountry();

    #ifdef ESP32

    // check for arduino or system event system, handle esp32 arduino v2 and IDF
    #if defined(ESP_ARDUINO_VERSION) && defined(ESP_ARDUINO_VERSION_VAL)

        #define WM_ARDUINOVERCHECK ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(2, 0, 0)
        #define WM_ARDUINOVERCHECK_204 ESP_ARDUINO_VERSION <= ESP_ARDUINO_VERSION_VAL(2, 0, 5)

        #ifdef WM_ARDUINOVERCHECK
            #define WM_ARDUINOEVENTS
        #else
            #define WM_NOSOFTAPSSID
            #define WM_NOCOUNTRY
        #endif

        #ifdef WM_ARDUINOVERCHECK_204
            #define WM_DISCONWORKAROUND
        #endif

    #else 
        #define WM_NOCOUNTRY
    #endif

    #ifdef WM_NOCOUNTRY
        #warning "ESP32 set country unavailable" 
    #endif


    #ifdef WM_ARDUINOEVENTS
        void   WiFiEvent(WiFiEvent_t event, arduino_event_info_t info);
    #else
        void   WiFiEvent(WiFiEvent_t event, system_event_info_t info);
    #endif
    #endif

    // output helpers
    String        getParamOut();
    String        getIpForm(String id, String title, String value);
    String        getScanItemOut();
    String        getStaticOut();
    String        getHTTPHead(String title);
    String        getMenuOut();
    //helpers
    boolean       isIp(String str);
    String        toStringIp(IPAddress ip);
    boolean       validApPassword();
    String        encryptionTypeStr(uint8_t authmode);
    void          reportStatus(String &page);
    String        getInfoData(String id);

    // flags
    boolean       connect             = false;
    boolean       abort               = false;
    boolean       reset               = false;
    boolean       configPortalActive  = false;
    boolean       webPortalActive     = false;
    boolean       portalTimeoutResult = false;
    boolean       portalAbortResult   = false;
    boolean       storeSTAmode        = true; // option store persistent STA mode in connectwifi 
    int           timer               = 0;    // timer for debug throttle for numclients, and portal timeout messages
    
    // WiFiManagerParameter
    int         _paramsCount          = 0;
    int         _max_params;
    WiFiManagerParameter** _params    = NULL;

    // debugging
    typedef enum {
        DEBUG_SILENT    = 0, // debug OFF but still compiled for runtime
        DEBUG_ERROR     = 1, // error only
        DEBUG_NOTIFY    = 2, // default stable,INFO
        DEBUG_VERBOSE   = 3, // move verbose info
        DEBUG_DEV       = 4, // development useful debugging info
        DEBUG_MAX       = 5  // MAX extra dev auditing, var dumps etc (MAX+1 will print timing,mem and frag info)
    } wm_debuglevel_t;

    boolean _debug  = true;
    String _debugPrefix = FPSTR(S_debugPrefix);

    wm_debuglevel_t debugLvlShow = DEBUG_VERBOSE; // at which level start showing [n] level tags

    // build debuglevel support
    // @todo use DEBUG_ESP_x?
    
    // Set default debug level
    #ifndef WM_DEBUG_LEVEL
    #define WM_DEBUG_LEVEL DEBUG_MAX
    #endif

    // override debug level OFF
    #ifdef WM_NODEBUG
    #undef WM_DEBUG_LEVEL
    #endif

    #ifdef WM_DEBUG_LEVEL
    uint8_t _debugLevel = (uint8_t)WM_DEBUG_LEVEL;
    #else 
    uint8_t _debugLevel = 0; // default debug level
    #endif

    // @todo use DEBUG_ESP_PORT ?
    #ifdef WM_DEBUG_PORT
    Print& _debugPort = WM_DEBUG_PORT;
    #else
    Print& _debugPort = Serial; // debug output stream ref
    #endif

    template <typename Generic>
    void        DEBUG_WM(Generic text);

    template <typename Generic>
    void        DEBUG_WM(wm_debuglevel_t level,Generic text);
    template <typename Generic, typename Genericb>
    void        DEBUG_WM(Generic text,Genericb textb);
    template <typename Generic, typename Genericb>
    void        DEBUG_WM(wm_debuglevel_t level, Generic text,Genericb textb);

    // callbacks
    // @todo use cb list (vector) maybe event ids, allow no return value
    std::function<void(WiFiManager*)> _apcallback;
    std::function<void()> _webservercallback;
    std::function<void()> _savewificallback;
    std::function<void()> _presavewificallback;
    std::function<void()> _presaveparamscallback;
    std::function<void()> _saveparamscallback;
    std::function<void()> _resetcallback;
    std::function<void()> _preotaupdatecallback = NULL;
    std::function<void(size_t current, size_t final)> _progressOtaUpdateCallback = NULL;
    std::function<void(bool success)> _postOtaUpdateCallback = NULL;
    std::function<void()> _configportaltimeoutcallback;

    template <class T>
    auto optionalIPFromString(T *obj, const char *s) -> decltype(  obj->fromString(s)  ) {
      return  obj->fromString(s);
    }
    auto optionalIPFromString(...) -> bool {
      // DEBUG_WM("NO fromString METHOD ON IPAddress, you need ESP8266 core 2.1.0 or newer for Custom IP configuration to work.");
      return false;
    }

};

#endif

// #endif
