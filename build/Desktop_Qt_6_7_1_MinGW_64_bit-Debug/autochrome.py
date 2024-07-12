import random
import datetime
from datetime import timedelta
import traceback
import psutil
import os
import re
import zipfile
import uuid
import json
import time
import undetected_chromedriver as uc
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.chrome.service import Service
from selenium.common.exceptions import TimeoutException, WebDriverException
from flask import Flask, request, jsonify
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.action_chains import ActionChains


def create_random_number_fix1(length):

    rand = random.Random()

    digits = "0123456789"
    return ''.join(rand.choice(digits) for _ in range(length))


class Trash1:
    @staticmethod
    def smethod_0(string_0):
        return int(string_0)

    @staticmethod
    def smethod_01(object_0, object_1):
        return object_0.split(object_1)

    @staticmethod
    def FD2A9229(int_0, int_1):
        return (int_0, int_1)  # Python doesn't have a direct equivalent to Point, so we use a tuple

    @staticmethod
    def C0910183(string_0, string_1):
        return string_0 != string_1

    @staticmethod
    def smethod_02(string_0):
        return not string_0

    @staticmethod
    def CEB1D508(object_0):
        return object_0.strip()

    @staticmethod
    def smethod_03(object_0, string_0):
        object_0.binary_location = string_0

    @staticmethod
    def F2898910(string_0, string_1, string_2, string_3):
        return string_0 + string_1 + string_2 + string_3

    @staticmethod
    def smethod_04(string_0, string_1, string_2):
        return string_0 + string_1 + string_2

    @staticmethod
    def E097A431(string_0):
        return ''.join(string_0)

    @staticmethod
    def F0B6EE93():
        return Service()  # This is the equivalent of ChromeDriverService.CreateDefaultService()

    @staticmethod
    def B40DCEA1(object_0):
        return object_0.window_handles


class JSON_Settings:

    def __init__(self, jsonStringOrPathFile, isJsonString=False):
        if isJsonString:
            if jsonStringOrPathFile.strip() == "":
                jsonStringOrPathFile = "{}"
            self.json = json.loads(jsonStringOrPathFile)
        else:
            try:
                self.PathFileSetting = os.path.join("settings", f"{jsonStringOrPathFile}.json")
                if not os.path.exists(self.PathFileSetting):
                    with open(self.PathFileSetting, 'w'):
                        pass
                with open(self.PathFileSetting, 'r') as file:
                    self.json = json.load(file)
            except:
                self.json = {}

    def convert_to_dictionary(self, jobject_1=None):
        C6870995 = {}
        try:
            if jobject_1 is None:
                jobject_1 = self.json
            C6870995 = jobject_1
            for key in list(C6870995.keys()):
                if isinstance(C6870995[key], dict):
                    C6870995[key] = self.convert_to_dictionary(C6870995[key])
                elif isinstance(C6870995[key], list):
                    C6870995[key] = [item for item in C6870995[key]]
        except:
            pass
        return C6870995

    def get_value(self, key, valueDefault=""):
        result = valueDefault
        try:
            result = self.json.get(key, valueDefault)
            return result
        except:
            return result

    def contains_key(self, key):
        return key in self.json

    def get_value_list(self, key, typesplitString=0):
        list_result = []
        try:
            if typesplitString != 0:
                list_result = self.get_value(key).split("\n|\n")
            else:
                list_result = self.get_value(key).split('\n')
            list_result = [item for item in list_result if item]
            return list_result
        except:
            return list_result

    def get_value_int(self, key, valueDefault=0):
        result = valueDefault
        try:
            result = int(self.json.get(key, valueDefault))
            return result
        except:
            return result

    def get_value_bool(self, key, valueDefault=False):
        result = valueDefault
        try:
            if self.json.get(key, valueDefault) == "True":
                result = True
            else:
                result = False
            print(self.json.get(key, valueDefault))
            return result
        except:
            return result

    def add(self, key, value):
        try:
            if key not in self.json:
                self.json[key] = value
            else:
                self.json[key] = value
        except Exception:
            pass

    def update(self, key, value):
        try:
            self.json[key] = str(value)
        except:
            pass

    def update_list(self, key, lst):
        try:
            flag = False
            for item in lst:
                if "\n" in item:
                    flag = True
                    break
            if flag:
                self.json[key] = "\n|\n".join(lst)
            else:
                self.json[key] = "\n".join(lst)
        except:
            pass

    def remove(self, key):
        try:
            self.json.pop(key, None)
        except:
            pass

    def save(self, pathFileSetting=""):
        try:
            if pathFileSetting == "":
                pathFileSetting = self.PathFileSetting
            with open(pathFileSetting, 'w') as file:
                json.dump(self.json, file, indent=4)
        except:
            pass

    def get_full_string(self):
        result = ""
        try:
            result = json.dumps(self.json).replace("\r\n", "")
            return result
        except Exception:
            return result


class SettingsTool:
    settings = {}

    @staticmethod
    def get_settings(key):
        if key not in SettingsTool.settings:
            SettingsTool.settings[key] = JSON_Settings(key)
        return SettingsTool.settings[key]

    @staticmethod
    def load_settings(key):
        SettingsTool.settings[key] = JSON_Settings(key)

    @staticmethod
    def save_settings(key):
        if key in SettingsTool.settings:
            SettingsTool.settings[key].save()
        SettingsTool.load_settings(key)

    @staticmethod
    def get_path_profile():
        text = SettingsTool.settings["configGeneral"].get_value("txbPathProfile")
        if "\\" not in text:
            text = os.path.join(FileHelper.get_path_to_current_folder(), "profiles" if text == "" else text)
        if not os.path.exists(text):
            return os.path.join(FileHelper.get_path_to_current_folder(), "profiles")
        return text

    @staticmethod
    def get_path_backup():
        return os.path.join(FileHelper.get_path_to_current_folder(), "backup")
    
class FileHelper:
    @staticmethod
    def get_path_to_current_folder():
        return os.path.dirname(os.path.abspath(__file__))

class Chrome:
    def __init__(self):
        self.index_chrome = 0
        self.hide_browser = False
        self.disable_image = False
        self.disable_sound = True
        self.incognito = False
        self.user_agent = ""
        self.profile_path = ""
        self.size = (300, 300)
        self.proxy = ""
        self.type_proxy = 0
        self.position = (0, 0)
        self.time_wait_for_searching_element = 3
        self.time_wait_for_loading_page = 60
        self.app = ""
        self.auto_play_video = False
        self.link_to_other_browser = ""
        self.path_extension = "data/extension"
        self.is_use_emulator = False
        self.size_emulator = (300, 300)
        self.status = "Empty"
        self.is_use_portable = False
        self.path_to_portable_zip = ""
        self.scale = 1.0
        self.driver = None
        self.process = None
        self.E82A933C = None
        self.EA173000 = False
        self.D5084A9D = False
        self.TimeWaitForSearchingElement = None
        self.TimeWaitForLoadingPage = None
        self.processChromeDriver = None
        self.chrome = None
        self.ACB9092E = None
        self.Int32_1 = None
    # @property
    # def getACB9092E(self):
    #     return self.ACB9092E
    # @ACB9092E.setter # type: ignore
    # def setACB9092E(self, value):
    #     self.ACB9092E = value
    def set_proxy(self, options):
        text = "\r\n            function callbackFn(details)\r\n            {\r\n\t            return {\r\n\t\t            {Auth}\r\n\t            };\r\n            }\r\n            chrome.webRequest.onAuthRequired.addListener(\r\n\t            callbackFn,\r\n\t            { urls:[\"<all_urls>\"] },\r\n                ['blocking']\r\n            );"
        newValue = ""
        text2 = ""
        newValue2 = ""
        if self.proxy == "":
            text2 = "direct"
        else:
            text3 = ""
            text4 = ""
            text2 = "fixed_servers"
            newValue = "\r\n                    rules: {\r\n                        singleProxy: {\r\n                            scheme: \"{TypeProxy}\",\r\n                            host: \"{HOST}\",\r\n                            port: parseInt({PORT})\r\n                        },\r\n                        bypassList: []\r\n\t                }\r\n                "
            if len(self.proxy.split(':')) == 1:
                text3 = "127.0.0.1"
                text4 = self.proxy
            elif len(self.proxy.split(':')) == 2:
                text3 = self.proxy.split(':')[0]
                text4 = self.proxy.split(':')[1]
            elif len(self.proxy.split(':')) == 4:
                text3 = self.proxy.split(':')[0]
                text4 = self.proxy.split(':')[1]
                newValue3 = self.proxy.split(':')[2]
                newValue4 = self.proxy.split(':')[3]
                newValue2 = "\r\n                            authCredentials:\r\n\t\t                    {\r\n\t\t\t                    username: \"{USERNAME}\",\r\n\t\t\t                    password: \"{PASSWORD}\"\r\n\t\t                    }\r\n                        "
                newValue2 = newValue2.replace("{USERNAME}", newValue3).replace("{PASSWORD}", newValue4)
            newValue = newValue.replace("{HOST}", text3).replace("{PORT}", str(text4)).replace("{TypeProxy}", "http" if self.type_proxy == 0 else "socks5")
            options.add_argument(f"--proxy-server={'socks5://' if self.type_proxy != 0 else ''}{text3}:{text4}")
            text = "\r\n            function callbackFn(details)\r\n            {\r\n\t            return {\r\n\t\t            {Auth}\r\n\t            };\r\n            }\r\n            chrome.webRequest.onAuthRequired.addListener(\r\n\t            callbackFn,\r\n\t            { urls:[\"<all_urls>\"] },\r\n                ['blocking']\r\n            );".replace("{Mode}", text2).replace("{Rules}", newValue).replace("{Auth}", newValue2)
            if not os.path.exists("Plugins"):
                os.makedirs("Plugins")
            text5 = str(uuid.uuid4())
            text6 = "Plugins/manifest_" + text5 + ".json"
            text7 = "Plugins/background_" + text5 + ".js"
            text8 = "Plugins/proxy_auth_plugin_" + text5 + ".zip"
            manifest_content = """
{
    "version": "1.0.0",
    "manifest_version": 2,
    "name": "Chrome Proxy",
    "permissions": [
        "proxy",
        "tabs",
        "unlimitedStorage",
        "storage",
        "<all_urls>",
        "webRequest",
        "webRequestBlocking"
    ],
    "background": {
        "scripts": ["background.js"]
    },
    "minimum_chrome_version": "22.0.0"
}
"""
            with open(text6, 'w') as file:
                file.write(manifest_content)
            with open(text7, 'w') as file:
                file.write(text)
            with zipfile.ZipFile(text8, 'w') as zipf:
                zipf.write(text6, "manifest.json")
                zipf.write(text7, "background.js")
            os.remove(text6)
            os.remove(text7)
            options.add_extension(text8)

    def open(self):
        if "x" in SettingsTool.get_settings("configGeneral").get_value("sizeChrome", ""):
            self.is_use_emulator = True
            text = SettingsTool.get_settings("configGeneral").get_value("sizeChrome", "").substring(0, SettingsTool.get_settings("configGeneral").get_value("sizeChrome", "").indexOf("x"))
            num = Trash1.smethod_0(Trash1.smethod_01(SettingsTool.get_settings("configGeneral").get_value("sizeChrome"), 'x')[2])
            self.size_emulator = Trash1.FD2A9229(
    Trash1.smethod_0(Trash1.smethod_01(text, 'x')[0]),
    Trash1.smethod_0(Trash1.smethod_01(text, 'x')[1])
)
            self.E82A933C = num
        self.link_to_other_browser = SettingsTool.get_settings("configGeneral").get_value("txtLinkToOtherBrowser", "").strip()
        self.is_use_portable = SettingsTool.get_settings("configGeneral").get_value_bool("ckbUsePortable", False)
        self.path_to_portable_zip = SettingsTool.get_settings("configGeneral").get_value("txtPathToPortableZip", "")
        if(self.hide_browser == False):
            self.hide_browser = SettingsTool.get_settings("configGeneral").get_value_bool("ckbHideBrowser", False)
        if self.EA173000 or self.D5084A9D:
            self.disable_image =False
            self.hide_browser = False
        if(self.hide_browser):
            self.disable_image = True
        result = False
        try:
            chrome_options = uc.ChromeOptions()
            chrome_options.add_argument(f"--window-size={self.size[0]},{self.size[1]}")
            chrome_options.add_argument(f"--window-position={self.position[0]},{self.position[1]}")

            chrome_options.add_argument("--disable-3d-apis")
            chrome_options.add_argument("--disable-background-networking")
            chrome_options.add_argument("--disable-bundled-ppapi-flash")
            chrome_options.add_argument("--disable-client-side-phishing-detection")
            chrome_options.add_argument("--disable-default-apps")
            chrome_options.add_argument("--disable-hang-monitor")
            chrome_options.add_argument("--disable-prompt-on-repost")
            chrome_options.add_argument("--disable-sync")
            chrome_options.add_argument("--disable-webgl")
            chrome_options.add_argument("--enable-blink-features=ShadowDOMV0")
            chrome_options.add_argument("--enable-logging")
            chrome_options.add_argument("--disable-notifications")
            chrome_options.add_argument("--no-sandbox")
            chrome_options.add_argument("--disable-gpu")
            chrome_options.add_argument("--disable-dev-shm-usage")
            chrome_options.add_argument("--disable-web-security")
            chrome_options.add_argument("--disable-rtc-smoothness-algorithm")
            chrome_options.add_argument("--disable-webrtc-hw-decoding")
            chrome_options.add_argument("--disable-webrtc-hw-encoding")
            chrome_options.add_argument("--disable-webrtc-multiple-routes")
            chrome_options.add_argument("--disable-webrtc-hw-vp8-encoding")
            chrome_options.add_argument("--enforce-webrtc-ip-permission-check")
            chrome_options.add_argument("--force-webrtc-ip-handling-policy")
            chrome_options.add_argument("--ignore-certificate-errors")
            chrome_options.add_argument("--disable-infobars")
            chrome_options.add_argument("--disable-blink-features=BlockCredentialedSubresources")
            chrome_options.add_argument("--disable-popup-blocking")
            chrome_options.add_argument("--no-default-browser-check")
            chrome_options.add_argument("--no-first-run")
            
            chrome_options.add_experimental_option("prefs", {
        "profile.default_content_setting_values.geolocation": 0,
        "profile.default_content_setting_values.images": 0,
        "credentials_enable_service": False
    })

            if self.disable_sound:
               chrome_options.add_argument("--mute-audio")

            chrome_options.add_argument("--app=https://mobile.facebook.com")
            chrome_options.add_argument("--disable-blink-features=AutomationControlled")
            # chrome_options.add_experimental_option("useAutomationExtension", False)
            # chrome_options.add_experimental_option("excludeSwitches", ["enable-automation"])

            if self.scale != 1.0:
              chrome_options.add_argument(f"--force-device-scale-factor={self.scale}")
              chrome_options.add_argument(f"high-dpi-support={self.scale}")

            if self.link_to_other_browser and os.path.exists(self.link_to_other_browser):
               chrome_options.binary_location = self.link_to_other_browser

            if self.hide_browser:
                chrome_options.add_argument("--headless=new")

            if self.disable_image:
                chrome_options.add_argument("--blink-settings=imagesEnabled=false")

            if self.profile_path.strip():
                 if self.is_use_portable:
                    if not os.path.exists(self.profile_path):
                         with zipfile.ZipFile(self.path_to_portable_zip, 'r') as zip_ref:
                             zip_ref.extractall(self.profile_path)
                    chrome_options.binary_location = os.path.join(self.profile_path, "App", "Chrome-bin", "chrome.exe")
                    check2 =os.path.join(self.profile_path, "App", "Chrome-bin", "chrome.exe")
                    check = f"--user-data-dir={os.path.join(self.profile_path, 'Data', 'profile')}"
                    chrome_options.add_argument(f"--user-data-dir={os.path.join(self.profile_path, 'Data', 'profile')}")
                 else:
                    try:
                        chrome_options.add_argument(f"--user-data-dir={self.profile_path}")
                        os.remove(os.path.join(self.profile_path, "Default", "Preferences"))
                    except Exception:
                       pass
            if self.incognito:
                  chrome_options.add_argument("--incognito")

    # Proxy setup
            if SettingsTool.get_settings("configGeneral").get_value_bool("ckbUseExtensionProxy"):
                  self.set_proxy(chrome_options)
            elif self.proxy.strip():
                 proxy_parts = self.proxy.split(':')
                 if len(proxy_parts) == 1:
                      chrome_options.add_argument(f"--proxy-server={'socks5://' if self.type_proxy != 0 else ''}127.0.0.1:{self.proxy}")
                 elif len(proxy_parts) == 2:
                     chrome_options.add_argument(f"--proxy-server={'socks5://' if self.type_proxy != 0 else ''}{self.proxy}")
                 elif len(proxy_parts) == 4:
                     chrome_options.add_argument(f"--proxy-server={'socks5://' if self.type_proxy != 0 else ''}{proxy_parts[0]}:{proxy_parts[1]}")
                     check = os.path.join(os.path.dirname(os.path.abspath(__file__)), "extension", "proxy1-ex")
                     chrome_options.add_argument(f'--load-extension={os.path.join(os.path.dirname(os.path.abspath(__file__)), "extension", "proxy1-ex")}')

            if self.user_agent:
                 chrome_options.add_argument(f"--user-agent={self.user_agent}")

            flag = False
            if self.path_extension.strip():
               if not os.path.exists(self.path_extension):
                     os.makedirs(self.path_extension)
               files = [f for f in os.listdir(self.path_extension) if os.path.isfile(os.path.join(self.path_extension, f))]
               if files:
                      flag = True
               for file in files:
                 chrome_options.add_extension(os.path.join(self.path_extension, file))

            if not flag and self.app.strip():
                chrome_options.add_argument(f"--app={self.app}")

            if self.auto_play_video:
                 chrome_options.add_argument("--autoplay-policy=no-user-gesture-required")
            self.chrome = uc.Chrome(
                options=chrome_options,
                suppress_welcome=True,
                headless=False
            )
            self.chrome.set_window_size(300,300)
            self.processChromeDriver = psutil.Process(self.chrome.service.process.pid)
            self.chrome.implicitly_wait(self.time_wait_for_searching_element)
            self.chrome.set_page_load_timeout(self.time_wait_for_loading_page)
            if(self.hide_browser == False):
                self.getProcess()
            if (not SettingsTool.get_settings("configGeneral").get_value_bool("ckbUseExtensionProxy") and len(self.proxy.split(':')) ==4 ):
                self.execute_script("document.title=\"proxyauth=" + self.proxy + "\"")
                num = SettingsTool.get_settings("configGeneral").get_value_int("nudDelayCheckIP")
                if num >3:
                    num =3
                self.delayTime(num)
                self.goto_url("https://ifconfig.co/ip")
                self.ACB9092E = str(self.chrome.session_id)
                self.Int32_1 = self
                result = True
                return result
        except Exception as e:
            print(f"An error occurred: {str(e)}")
    def get_page_source(self):
        if self.checkChromeClose():
            return "-2"
        try:
            return self.chrome.page_source
        except Exception as ex:
            print(f"An error occurred: {str(ex)}")
            return ""
    def goto_url(self, url):
        if self.checkChromeClose():
            return -2

        success = False
        for i in range(2):
            try:
                if i == 0:
                    self.chrome.set_page_load_timeout(5)
                else:
                    self.chrome.set_page_load_timeout(self.time_wait_for_loading_page)
                
                self.chrome.get(url)
                success = True
                break
            except (TimeoutException, WebDriverException):
                continue

        self.chrome.set_page_load_timeout(self.time_wait_for_loading_page)
        return 1 if success else 0
    def execute_script(self, script):
        if self.checkChromeClose():
            return -2
        
        try:
            return self.chrome.execute_script(script)
        except Exception as ex:
            self.export_error(None, ex, f"chrome.execute_script({script})")
        
        return ""
    def getProcess(self):
        try:
            if(self.process == None):
                return True
            title = ""
            for _ in range(10):
                try:
                    try:
                        title = self.chrome.current_window_handle
                    except Exception:
                        title = create_random_number_fix1(15)
                    if title != "":
                        for _ in range(30):
                            self.chrome.execute_script("document.title='" + title + "'")
                            self.delayTime(1.0)
                            chrome_processes = [p for p in psutil.process_iter(['name', 'cmdline']) 
                                                if p.name().lower() in ['chrome', 'chromium']]
                            for pro in chrome_processes:
                                try:
                                    if title in pro.cmdline():
                                        self.process = pro
                                        return True
                                except (psutil.NoSuchProcess, psutil.AccessDenied):
                                    pass
                except:
                    pass
                self.delayTime(1.0)
        except Exception as e:
            print(f"An error occurred: {str(e)}")
            return False
    def delayTime(self, timeDelay_Seconds):
        try:
            if(self.checkChromeClose() == False):
                time.sleep(timeDelay_Seconds)
        except:
            pass
    def checkChromeClose(self):
        if not self.process == None:
            return self.process.is_running()
        result = True
        try:
            _ = self.chrome.title
            result = False
        except Exception as e:
            print(f"An error occurred: {str(e)}")
        return result
    def convert_css_selector_to_js_dom(self,css_selectors_or_xpath):
        if css_selectors_or_xpath.startswith("/") or css_selectors_or_xpath.startswith("(/"):
            css_selectors_or_xpath = css_selectors_or_xpath.replace("'", "\\'")
            return f"document.evaluate('{css_selectors_or_xpath}', document, null, XPathResult.FIRST_ORDERED_NODE_TYPE, null).singleNodeValue"
        
        text = ""
        text2 = ""
        value = 0
        num = 0
        
        array = css_selectors_or_xpath.split('|')
        array_length = len(array)
        
        if array_length == 1:
            text = array[0].strip()
        elif array_length == 2:
            text = array[0].strip()
            value = int(array[1].strip())
        elif array_length == 3:
            text = array[0].strip()
            value = int(array[1].strip())
            text2 = array[2].strip()
        elif array_length == 4:
            text = array[0].strip()
            value = int(array[1].strip())
            text2 = array[2].strip()
            num = int(array[3].strip())
        
        if num != 0:
            return f"document.querySelectorAll('{text.replace("'", "\\'")}')[{value}].querySelectorAll('{text2.replace("'", "\\'")}')[{num}]"
        
        return f"document.querySelectorAll('{text.replace("'", "\\'")}')[{value}]"
    def check_exist_element(self,css_selectors_or_xpath, time_wait_second=0.0):
        if self.checkChromeClose():
            return -2
    
        try:
            start_time = time.time()
            while True:
                js_dom = self.convert_css_selector_to_js_dom(css_selectors_or_xpath)
                if self.execute_script(f"return {js_dom}!=null") == True:
                    return 1
    
                if self.checkChromeClose():
                    return -2
    
                if time_wait_second != 0.0:
                    self.delayTime(1.0)
                    if time.time() - start_time >= time_wait_second:
                        break
                else:
                    break
        except Exception as ex:
            print(f"An error occurred: {str(ex)}")
    
        return 0
    def get_url(self):
        if self.checkChromeClose():
            return "-2"
        try:
            return self.chrome.current_url
        except Exception:
            pass
        return ""
    def getFbWeb(self, url = ""):
        if(url == ""):
            url = self.get_url()
        result = 0
        if url.startswith("https://www.facebook") or url.startswith("https://facebook") or url.startswith("https://web.facebook"):
            result = 1
        elif  url.startswith("https://m.facebook") or url.startswith("https://d.facebook") or url.startswith("https://mobile.facebook"):
            result = 2
        elif url.startswith("https://mbasic.facebook"):
            result = 3
        return result
    def clickJS(self, css_selectors_or_xpath):
        try:
            self.chrome.execute_script(f"{self.convert_css_selector_to_js_dom(css_selectors_or_xpath)}.click()")
            return True
        except Exception:
            pass
        return False
    def accept_cookie(self):
        for _ in range(4):
            if self.getFbWeb() == 1:
                if self.clickJS("[role=\"dialog\"] [aria-label=\"Close\"],[role=\"dialog\"] [aria-label][role=\"button\"]:has(svg)"):
                    self.delayTime(2.0)
                break
    
            if self.check_exist_element("[data-cookiebanner=\"accept_button\"]") == 1:
                self.execute_script("document.querySelector('[data-cookiebanner=\"accept_button\"]').click()")
                continue
    
            url = self.get_url()
            if url.startswith("https://m.facebook.com/si/actor_experience/actor_gateway") and self.check_exist_element("[data-nt=\"NT:IMAGE\"]", 15.0) == 1:
                self.execute_script("document.querySelector('[data-nt=\"NT:IMAGE\"]').click()")
                self.delayTime(2.0)
                continue
    
            if "facebook.com/legal_consent" in url:
                self.clickJS("button[type=\"submit\"]")
                self.delayTime(1.0)
                self.clickJS("button[type=\"submit\"]:last-child")
                self.delayTime(1.0)
                self.clickJS("button[type=\"submit\"]")
                self.delayTime(1.0)
                self.clickJS("#consent-page-container button[type=\"submit\"]:last-child")
                self.delayTime(1.0)
                continue
    
            if "facebook.com/privacy/consent_framework/prompt/" in url:
                checkboxes = [
                    "[type=\"checkbox\"][name=\"personal_data_toggle\"]",
                    "[type=\"checkbox\"][name=\"data_shared_3pd_toggle\"]",
                    "[type=\"checkbox\"][name=\"cross_border_data_transfer_toggle\"]",
                    "[type=\"checkbox\"][name=\"location_info_toggle\"]"
                ]
                for checkbox in checkboxes:
                    if self.check_exist_element(checkbox) == 1:
                        self.execute_script(f"document.querySelector('{checkbox}').checked=true;")
                
                self.clickJS("button[name=\"primary_consent_button\"]")
                self.delayTime(2.0)
                continue
    
            break
    def check_exist_elements(self, time_out, lst_css_selectors):
        if self.checkChromeClose():
            return -2
        
        try:
            start_time = time.time()
            while True:
                selectors_string = '|'.join(lst_css_selectors)
                script = f"""
                var arr = '{selectors_string}'.split('|');
                var output = 0;
                for (i = 0; i < arr.length; i++) {{
                    if (document.querySelectorAll(arr[i]).length > 0) {{
                        output = i + 1;
                        break;
                    }}
                }}
                return output.toString();
                """
                result = self.execute_script(script)
                
                if result != 0:
                    return result
                
                if time.time() - start_time > time_out:
                    time.sleep(1)
                    continue
                break                    
            return result
        except Exception:
            return result
        


    def getattribute_value(self, cssSelectorsOrXpath, attributeName):
        result =""
        if self.checkChromeClose():
            return "-2"
        try:
            result = self.chrome.execute_script(f"return {self.convert_css_selector_to_js_dom(cssSelectorsOrXpath)}.getAttribute('{attributeName}')")
            return result
        except Exception:
            return result
        


    def find_and_click(self, time_wait_seconds, type_attribute, attribute_value, index=0, sub_type_attribute=0, sub_attribute_value="", sub_index=0):
        if self.checkChromeClose():
            return -2
    
        try:
            start_time = time.time()
            while True:
                try:
                    if sub_type_attribute == 0:
                        if type_attribute == 1:
                            self.chrome.find_elements(By.ID, attribute_value)[index].click()
                        elif type_attribute == 2:
                            self.chrome.find_elements(By.NAME, attribute_value)[index].click()
                        elif type_attribute == 3:
                            self.chrome.find_elements(By.XPATH, attribute_value)[index].click()
                        elif type_attribute == 4:
                            self.chrome.find_elements(By.CSS_SELECTOR, attribute_value)[index].click()
                    else:
                        if type_attribute == 1:
                            self.chrome.find_elements(By.ID, attribute_value)[index].find_elements(By.ID, sub_attribute_value)[sub_index].click()
                        elif type_attribute == 2:
                            self.chrome.find_elements(By.NAME, attribute_value)[index].find_elements(By.NAME, sub_attribute_value)[sub_index].click()
                        elif type_attribute == 3:
                            self.chrome.find_elements(By.XPATH, attribute_value)[index].find_elements(By.XPATH, sub_attribute_value)[sub_index].click()
                        elif type_attribute == 4:
                            self.chrome.find_elements(By.CSS_SELECTOR, attribute_value)[index].find_elements(By.CSS_SELECTOR, sub_attribute_value)[sub_index].click()
                    
                    time.sleep(1)
                    return 1
                except IndexError:
                    if time.time() - start_time >= time_wait_seconds:
                        return 0
                    time.sleep(1)
        except Exception as ex:
            self.export_error(None, ex, f"chrome.find_and_click({time_wait_seconds},{type_attribute},{attribute_value},{index},{sub_type_attribute},{sub_attribute_value},{sub_index}")
            return 0
        


    def send_keys_with_speed(self, toc_do, type_attribute, attribute_value, content, time_delay_second, is_click=True, time_delay_after_click=0.1):
        if self.checkChromeClose():
            return -2
    
        result = 0
        if toc_do == 0:
            result = self.send_keys(type_attribute, attribute_value, content, time_delay_second, is_click, time_delay_after_click)
        elif toc_do == 1:
            result = self.send_keys(type_attribute, attribute_value, content, time_delay_second, is_click, time_delay_after_click)
        elif toc_do == 2:
            result = self.send_keys(type_attribute, attribute_value, content, is_click, time_delay_after_click)
    
        return result

    def send_keys(self, type_attribute, attribute_value, content, time_delay_second, is_click=True, time_delay_after_click=0.1):
        if self.checkChromeClose():
            return -2

        try:
            if is_click:
                self.click(type_attribute, attribute_value)
                self.delayTime(time_delay_after_click)

            num = 0
            num2 = random.randint(0, 2)
            if len(content) < 3:
                num2 = 2
            else:
                num = random.randint(1, len(content) * 3 // 4)

            if num2 == 0:
                content4 = content[:num]
                self.send_keys(random, type_attribute, attribute_value, content4, random.randint(10, 100) / 1000.0)
                self.delayTime(random.randint(1, 3))
                num3 = random.randint(1, num)
                for _ in range(num3):
                    self.send_backspace(type_attribute, attribute_value)
                    self.delayTime(random.randint(1000, 2000) / 10000.0)

                text = ""
                if type_attribute == 1:
                    text = f"#{attribute_value}"
                elif type_attribute == 2:
                    text = f'[name="{attribute_value}"]'
                elif type_attribute == 4:
                    text = attribute_value

                current_value = self.execute_script(f"return document.querySelector('{text}').value+''")
                content4 = content[len(current_value):]
                self.delayTime(random.randint(1, 3))
                self.send_keys(random, type_attribute, attribute_value, content4, random.randint(100, 300) / 1000.0, False)
                self.delayTime(random.randint(1, 3))

            elif num2 == 1:
                content2 = content[:num]
                content3 = content[num:]
                self.send_keys(random, type_attribute, attribute_value, content2, random.randint(10, 100) / 1000.0)
                self.delayTime(random.randint(1, 3))
                self.send_keys(random, type_attribute, attribute_value, content3, random.randint(100, 300) / 1000.0, False)
                self.delayTime(random.randint(1, 3))

            else:  # num2 == 2
                self.send_keys(random, type_attribute, attribute_value, content, random.randint(100, 200) / 1000.0)
                self.delayTime(random.randint(1, 3))

            return 1
        except Exception as ex:
            self.export_error(None, ex, f"chrome.send_keys({type_attribute},{attribute_value},{content},{time_delay_second},{is_click})")
            return 0

    def send_backspace(self, type_attribute, attribute_value):
        if self.checkChromeClose():
            return -2

        try:
            if type_attribute == 1:
                self.chrome.find_element(By.ID, attribute_value).send_keys(Keys.BACKSPACE)
            elif type_attribute == 2:
                self.chrome.find_element(By.NAME, attribute_value).send_keys(Keys.BACKSPACE)
            elif type_attribute == 3:
                self.chrome.find_element(By.XPATH, attribute_value).send_keys(Keys.BACKSPACE)
            elif type_attribute == 4:
                self.chrome.find_element(By.CSS_SELECTOR, attribute_value).send_keys(Keys.BACKSPACE)
            else:
                return 0
            return 1
        except WebDriverException as ex:
            self.export_error(None, ex, f"chrome.send_backspace({type_attribute}, {attribute_value})")
            return 0


    def click(self, typeAttribute, attributeValue, index=0, subTypeAttribute=0, subAttributeValue="", subIndex=0, times=1):
        flag = False
        if self.checkChromeClose():
            return -2
        
        for i in range(times):
            time.sleep(1.0)  # Simulate DelayTime(1.0) in C#
            try:
                if subTypeAttribute == 0:
                    if typeAttribute == 1:
                        self.chrome.find_elements(By.ID, attributeValue)[index].click()
                    elif typeAttribute == 2:
                        self.chrome.find_elements(By.NAME, attributeValue)[index].click()
                    elif typeAttribute == 3:
                        self.chrome.find_elements(By.XPATH, attributeValue)[index].click()
                    elif typeAttribute == 4:
                        self.chrome.find_elements(By.CSS_SELECTOR, attributeValue)[index].click()
                else:
                    if typeAttribute == 1:
                        self.chrome.find_elements(By.ID, attributeValue)[index].find_elements(By.ID, subAttributeValue)[subIndex].click()
                    elif typeAttribute == 2:
                        self.chrome.find_elements(By.NAME, attributeValue)[index].find_elements(By.NAME, subAttributeValue)[subIndex].click()
                    elif typeAttribute == 3:
                        self.chrome.find_elements(By.XPATH, attributeValue)[index].find_elements(By.XPATH, subAttributeValue)[subIndex].click()
                    elif typeAttribute == 4:
                        self.chrome.find_elements(By.CSS_SELECTOR, attributeValue)[index].find_elements(By.CSS_SELECTOR, subAttributeValue)[subIndex].click()
                
                flag = True
            except Exception as ex:
                self.export_error(None, ex, f"chrome.Click({typeAttribute},{attributeValue})")
                continue
            
            break
        
        if not flag:
            return 0
        
        return 1


    def send_keys(self, type_attribute, attribute_value, content, time_delay_second, is_click=True, time_delay_after_click=0.1):
        if self.checkChromeClose():
            return -2

        try:
            if is_click:
                self.click(type_attribute, attribute_value)
                self.delayTime(time_delay_after_click)

            for char in content:
                if type_attribute == 1:
                    self.chrome.find_element(By.ID, attribute_value).send_keys(char)
                elif type_attribute == 2:
                    self.chrome.find_element(By.NAME, attribute_value).send_keys(char)
                elif type_attribute == 3:
                    self.chrome.find_element(By.XPATH, attribute_value).send_keys(char)
                elif type_attribute == 4:
                    self.chrome.find_element(By.CSS_SELECTOR, attribute_value).send_keys(char)

                if time_delay_second > 0:
                    delay_ms = int(time_delay_second * 1000)
                    delay_ms = max(delay_ms, 100)
                    time.sleep(random.randint(delay_ms, delay_ms + 50) / 1000)

            return 1
        except Exception as ex:
            self.export_error(None, ex, f"chrome.send_keys({type_attribute},{attribute_value},{content},{time_delay_second},{is_click})")
            return 0

    def export_error(self, ex, error=""):
        try:
            if error != "chrome.Open()":
                return
    
            for directory in ["log", "log/html", "log/images"]:
                os.makedirs(directory, exist_ok=True)
    
            timestamp = datetime.datetime.now().strftime("%d_%m_%Y_%H_%M_%S")
            random_number = random.randint(1000, 9999)
            filename = f"{timestamp}_{random_number}"
    
            if self.chrome is not None:
                contents = self.chrome.execute_script("var markup = document.documentElement.innerHTML;return markup;")
                self.chrome.save_screenshot(f"log/images/{filename}.png")
                with open(f"log/html/{filename}.html", "w", encoding="utf-8") as f:
                    f.write(contents)
    
            with open("log/log.txt", "a", encoding="utf-8") as f:
                f.write("-----------------------------------------------------------------------------\n")
                f.write(f"Date: {datetime.datetime.now().strftime('%d/%m/%Y %H:%M:%S')}\n")
                f.write(f"File: {filename}\n")
                if error:
                    f.write(f"Error: {error}\n")
                f.write("\n")
    
                if ex is not None:
                    f.write(f"Type: {type(ex).__name__}\n")
                    f.write(f"Message: {str(ex)}\n")
                    f.write(f"StackTrace: {''.join(traceback.format_tb(ex.__traceback__))}\n")
    
        except Exception:
            pass  # Silently handle any exceptions in the error logging process

    def send_enter(self, type_attribute, attribute_value, index=0, sub_type_attribute=0, sub_attribute_value="", sub_index=0):
        if self.checkChromeClose():
            return -2
    
        try:
            if sub_type_attribute == 0:
                if type_attribute == 1:
                    self.chrome.find_elements(By.ID, attribute_value)[index].send_keys(Keys.ENTER)
                elif type_attribute == 2:
                    self.chrome.find_elements(By.NAME, attribute_value)[index].send_keys(Keys.ENTER)
                elif type_attribute == 3:
                    self.chrome.find_elements(By.XPATH, attribute_value)[index].send_keys(Keys.ENTER)
                elif type_attribute == 4:
                    self.chrome.find_elements(By.CSS_SELECTOR, attribute_value)[index].send_keys(Keys.ENTER)
            else:
                if type_attribute == 1:
                    self.chrome.find_elements(By.ID, attribute_value)[index].find_elements(By.ID, sub_attribute_value)[sub_index].send_keys(Keys.ENTER)
                elif type_attribute == 2:
                    self.chrome.find_elements(By.NAME, attribute_value)[index].find_elements(By.NAME, sub_attribute_value)[sub_index].send_keys(Keys.ENTER)
                elif type_attribute == 3:
                    self.chrome.find_elements(By.XPATH, attribute_value)[index].find_elements(By.XPATH, sub_attribute_value)[sub_index].send_keys(Keys.ENTER)
                elif type_attribute == 4:
                    self.chrome.find_elements(By.CSS_SELECTOR, attribute_value)[index].find_elements(By.CSS_SELECTOR, sub_attribute_value)[sub_index].send_keys(Keys.ENTER)
    
            return 1
        except Exception as ex:
            self.export_error(None, ex, f"chrome.send_enter({type_attribute},{attribute_value},{index})")
            return 0
    
    def send_keys(self, type_attribute, attribute_value, content, is_click=True, time_delay_after_click=0.1):
        if self.checkChromeClose():
            return -2
        
        try:
            if is_click:
                self.click(type_attribute, attribute_value)
                self.delayTime(time_delay_after_click)
            
            element = None
            if type_attribute == 1:
                element = self.chrome.find_element(By.ID, attribute_value)
            elif type_attribute == 2:
                element = self.chrome.find_element(By.NAME, attribute_value)
            elif type_attribute == 3:
                element = self.chrome.find_element(By.XPATH, attribute_value)
            elif type_attribute == 4:
                element = self.chrome.find_element(By.CSS_SELECTOR, attribute_value)
            
            if element:
                element.send_keys(content)
                return 1
            else:
                return 0
        except Exception as ex:
            self.export_error(None, ex, f"chrome.send_keys({type_attribute},{attribute_value},{content},{is_click})")
            return 0
        
    def click_js(self, timeout=0, *css_selectors):
        if self.checkChromeClose():
            return -2
        
        try:
            text = self.check_exist_elements(timeout, list(css_selectors))
            if text:
                flag = self.clickJS(text)
            else:
                flag = False
        except Exception:
            flag = False
        
        return 1 if flag else 0
    
    def count_element(self, query_selector):
        result = 0
        if self.checkChromeClose():
            return -2
        
        try:
            js_code = f"return document.querySelectorAll('{query_selector.replace("'", "\\'")}').length+''"
            result = int(self.chrome.execute_script(js_code))
            return result
        except Exception as ex:
            self.export_error(None, ex, f"chrome.count_element({query_selector})")
            return result
        
    def click_with_action(self, type_attribute, attribute_value, index=0, sub_type_attribute=0, sub_attribute_value="", sub_index=0):
        if self.checkChromeClose():
            return -2
    
        try:
            if sub_type_attribute != 0:
                if type_attribute == 1:
                    element = self.chrome.find_elements(By.ID, attribute_value)[index].find_elements(By.ID, sub_attribute_value)[sub_index]
                elif type_attribute == 2:
                    element = self.chrome.find_elements(By.NAME, attribute_value)[index].find_elements(By.NAME, sub_attribute_value)[sub_index]
                elif type_attribute == 3:
                    element = self.chrome.find_elements(By.XPATH, attribute_value)[index].find_elements(By.XPATH, sub_attribute_value)[sub_index]
                elif type_attribute == 4:
                    element = self.chrome.find_elements(By.CSS_SELECTOR, attribute_value)[index].find_elements(By.CSS_SELECTOR, sub_attribute_value)[sub_index]
            else:
                if type_attribute == 1:
                    element = self.chrome.find_elements(By.ID, attribute_value)[index]
                elif type_attribute == 2:
                    element = self.chrome.find_elements(By.NAME, attribute_value)[index]
                elif type_attribute == 3:
                    element = self.chrome.find_elements(By.XPATH, attribute_value)[index]
                elif type_attribute == 4:
                    element = self.chrome.find_elements(By.CSS_SELECTOR, attribute_value)[index]
    
            ActionChains(self.chrome).click(element).perform()
            flag = True
        except Exception as ex:
            self.export_error(None, ex, f"chrome.click_with_action({type_attribute},{attribute_value})")
            flag = False
    
        return 1 if flag else 0
    
    def send_enter(self, css_selectors_or_xpath):
        if self.checkChromeClose():
            return -2
    
        try:
            self.get_element(css_selectors_or_xpath).send_keys(Keys.ENTER)
            flag = True
        except Exception:
            flag = False
    
        return 1 if flag else 0
    
    def get_element(self, css_selectors_or_xpath):
        if css_selectors_or_xpath.startswith("/") or css_selectors_or_xpath.startswith("(/"):
            return self.chrome.find_element(By.XPATH, css_selectors_or_xpath)
    
        css_selector = ""
        css_selector_to_find = ""
        index = 0
        sub_index = 0
    
        parts = css_selectors_or_xpath.split('|')
        
        if len(parts) == 1:
            css_selector = parts[0].strip()
        elif len(parts) == 2:
            css_selector = parts[0].strip()
            index = int(parts[1].strip())
        elif len(parts) == 3:
            css_selector = parts[0].strip()
            index = int(parts[1].strip())
            css_selector_to_find = parts[2].strip()
        elif len(parts) == 4:
            css_selector = parts[0].strip()
            index = int(parts[1].strip())
            css_selector_to_find = parts[2].strip()
            sub_index = int(parts[3].strip())
    
        if sub_index == 0:
            return self.chrome.find_elements(By.CSS_SELECTOR, css_selector)[index]
        else:
            return self.chrome.find_elements(By.CSS_SELECTOR, css_selector)[index].find_elements(By.CSS_SELECTOR, css_selector_to_find)[sub_index]
        


    def screen_capture(self, image_path, file_name):
        flag = False
        if self.checkChromeClose():
            return -2
        
        try:
            full_path = os.path.join(image_path, f"{file_name}.png")
            self.chrome.get_screenshot_as_file(full_path)
            flag = True
        except Exception as ex:
            self.export_error(None, ex, f"chrome.screen_capture({image_path},{file_name})")
        
        return 1 if flag else 0
    

    def get_cookie(self, domain="facebook"):
        text = ""
        if self.checkChromeClose():
            return ""
        
        try:
            cookies = self.chrome.get_cookies()
            for cookie in cookies:
                if domain in cookie['domain']:
                    text += f"{cookie['name']}={cookie['value']};"
            return text
        except Exception as ex:
            self.export_error(None, ex, f"chrome.GetCookieFromChrome({domain})")
            return text


    def get_uid(self):
        cookie_string = self.get_cookie()
        match = re.search(r"c_user=(\d+)", cookie_string)
        if match:
            return match.group(1)
        return ""

    def click_with_action(self, css_selectors_or_xpath):
        if self.checkChromeClose():
            return -2
        try:
            element = self.get_element(css_selectors_or_xpath)
            ActionChains(self.chrome).click(element).perform()
            return 1
        except Exception:
            pass
        return 0

    def click(self, css_selectors_or_xpath):
        try:
            self.get_element(css_selectors_or_xpath).click()
            return True
        except Exception:
            pass
        return False

    def goto_url_if_not_exist(self, url):
        flag = False
        if self.checkChromeClose():
            return -2
        try:
            if self.get_url() != url:
                self.chrome.get(url)
            flag = True
        except Exception as ex:
            self.export_error(None, ex, f"chrome.GotoURL({url})")
        
        if not flag:
            return 0
        return 1



    def add_cookie_into_chrome(self, cookie, domain=".facebook.com"):
        if self.checkChromeClose():
            return -2
        try:
            cookie_list = cookie.split(';')
            for cookie_item in cookie_list:
                cookie_item = cookie_item.strip()
                if cookie_item:
                    key_value = cookie_item.split('=', 1)
                    if len(key_value) > 1 and key_value[0].strip():
                        name = key_value[0].strip()
                        value = key_value[1].strip()
                        self.chrome.add_cookie({
                            'name': name,
                            'value': value,
                            'domain': domain,
                            'path': '/',
                            'expires': (datetime.now() + timedelta(days=10)).timestamp()
                        })
            return 1
        except Exception as ex:
            self.export_error(None, ex, f"chrome.AddCookieIntoChrome({cookie},{domain})")
            return 0
        
    def refresh(self):
        flag = False
        if self.checkChromeClose():
            return -2
        try:
            self.chrome.refresh()
            flag = True
        except WebDriverException as ex:
            self.export_error(None, ex, "chrome.Refresh()")
        
        if not flag:
            return 0
        return 1
    

app = Flask(__name__)
chrome_instances: list[Chrome] = []

@app.route('/create_instance', methods=['POST'])
def create_instance():
    data = request.json
    try:
        index_chrome = data.get("indexChrome")
        disable_image = data.get("disableImage")
        user_agent = data.get("userAgent")
        profile_path = data.get("profilePath")
        size = tuple(data.get("size"))
        position = tuple(data.get("position"))
        time_wait_for_searching_element = data.get("timeWaitForSearchingElement", 3)
        time_wait_for_loading_page = data.get("timeWaitForLoadingPage", 120)
        proxy = data.get("proxy")
        type_proxy = data.get("typeProxy")
        disable_sound = data.get("disableSound", True)
        app_url = data.get("app")
        is_use_portable = data.get("isUsePortable", SettingsTool.get_settings("configGeneral").get_value_bool("ckbUsePortable"))
        path_to_portable_zip = data.get("pathToPortableZip", SettingsTool.get_settings("configGeneral").get_value("txtPathToPortableZip"))

        chrome_instance = Chrome()
        chrome_instance.index_chrome = index_chrome
        chrome_instance.disable_image = disable_image
        chrome_instance.user_agent = user_agent
        chrome_instance.profile_path = profile_path
        chrome_instance.size = size
        chrome_instance.position = position
        chrome_instance.time_wait_for_searching_element = time_wait_for_searching_element
        chrome_instance.time_wait_for_loading_page = time_wait_for_loading_page
        chrome_instance.proxy = proxy
        chrome_instance.type_proxy = type_proxy
        chrome_instance.disable_sound = disable_sound
        chrome_instance.app = app_url
        chrome_instance.is_use_portable = is_use_portable
        chrome_instance.path_to_portable_zip = path_to_portable_zip

        for c in chrome_instances:
           if c.index_chrome == index_chrome:
              print("Instance already exists")
              return jsonify({"status": "error", "message": "Instance already exists"}), 400
        chrome_instances.append(chrome_instance)
        return jsonify({"status": "success", "instance_id": index_chrome}), 200

    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

@app.route('/click/<instance_id>', methods=['POST'])
def api_click(instance_id):
    chromeInstance = next((c for c in chrome_instances if c.index_chrome == int(instance_id)), None)
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404

    data = request.json
    if not data:
        return jsonify({"status": "error", "message": "No data provided"}), 400

    typeAttribute = data.get('typeAttribute')
    attributeValue = data.get('attributeValue')
    index = data.get('index', 0)
    subTypeAttribute = data.get('subTypeAttribute', 0)
    subAttributeValue = data.get('subAttributeValue', "")
    subIndex = data.get('subIndex', 0)
    times = data.get('times', 1)

    if typeAttribute is None or attributeValue is None:
        return jsonify({"status": "error", "message": "Missing required parameters"}), 400

    try:
        result = chromeInstance.click(
            typeAttribute, attributeValue, index, subTypeAttribute, subAttributeValue, subIndex, times
        )
        if result == 1:
            return jsonify({"status": "success", "message": "Click operation successful"}), 200
        elif result == -2:
            return jsonify({"status": "error", "message": "Chrome instance is closed"}), 500
        else:
            return jsonify({"status": "error", "message": "Click operation failed"}), 500
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500


@app.route('/open/<instance_id>', methods=['GET'])
def open_browser(instance_id):
    chromeInstance = None
    for c in chrome_instances:
        if c.index_chrome == int(instance_id):
            chromeInstance = c
            break
    if chromeInstance is None:
        print("Instance not found")
        return jsonify({"status": "error", "message": "Instance not found"}), 404
    try:
        chromeInstance.open()
        return jsonify({"status": "success", "message": "Browser opened"}), 200
    except Exception as e:
        print(f"An error occurred: {str(e)}")
        return jsonify({"status": "error", "message": str(e)}), 500

@app.route('/get_page_source/<instance_id>', methods=['GET'])
def get_page_source(instance_id):
    chromeInstance = None
    for c in chrome_instances:
        if c.index_chrome == int(instance_id):
            chromeInstance = c
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404
    result = chromeInstance.get_page_source()
    if not result == "-2" and result == "":
        return jsonify({"status": "error", "message": "Chrome is Close or Error"}), 500
    else:
        return jsonify({"status": "success", "message": "Get Page Source Success", "page_source": result}), 200

@app.route('/click_js/<int:instance_id>', methods=['POST'])
def api_click_js(instance_id):
    chromeInstance = next((c for c in chrome_instances if c.index_chrome == instance_id), None)
    
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404

    data = request.json
    timeout = data.get('timeout', 0)
    css_selectors = data.get('css_selectors', [])

    result = chromeInstance.click_js(timeout, *css_selectors)

    if result == -2:
        return jsonify({"status": "error", "message": "Chrome is closed"}), 500
    elif result == 1:
        return jsonify({"status": "success", "message": "Click JS successful"}), 200
    else:
        return jsonify({"status": "error", "message": "Click JS failed"}), 400

@app.route('/goto_url/<instance_id>', methods=['POST'])
def goto_url(instance_id):
    chromeInstance = None
    for c in chrome_instances:
        if c.index_chrome == int(instance_id):
            chromeInstance = c
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404
    url = request.json.get('url')
    if not url:
        return jsonify({"status": "error", "message": "URL not provided"}), 400
    result = chromeInstance.goto_url(url)
    if result == 1:
        return jsonify({"status": "success", "message": f"Navigated to {url}"}), 200
    else:
        return jsonify({"status": "error", "message": f"Failed to navigate to {url}"}), 500

@app.route('/execute_script/<instance_id>', methods=['POST'])
def execute_script(instance_id):
    chromeInstance = None
    for c in chrome_instances:
        if c.index_chrome == int(instance_id):
            chromeInstance = c
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404
    script = request.json.get('script')
    if not script:
        return jsonify({"status": "error", "message": "Script not provided"}), 400
    result = chromeInstance.execute_script(script)
    if result and not result == "-2":
        return jsonify({"status": "success", "result": result}), 200
    else:
        return jsonify({"status": "error", "message": "Failed to execute script"}), 500

@app.route('/check_chrome_close/<instance_id>', methods=['GET'])
def check_chrome_close(instance_id):
    chromeInstance = None
    for c in chrome_instances:
        if c.index_chrome == int(instance_id):
            chromeInstance = c
    if chromeInstance is None:
        print("Instance not found")
        return jsonify({"status": "error", "message": "Instance not found"}), 404
    result = chromeInstance.checkChromeClose()
    if result:
        return jsonify({"status": "success", "is_closed": result}), 200
    else:
        print("Failed to check")
        return jsonify({"status": "error", "message": "Failed to check"}), 500

@app.route('/delay_time/<instance_id>', methods=['POST'])
def delay_time(instance_id):
    chromeInstance = None
    for c in chrome_instances:
        if c.index_chrome == int(instance_id):
            chromeInstance = c
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404
    time_delay = request.json.get('time_delay')
    if time_delay is None:
        return jsonify({"status": "error", "message": "Time delay not provided"}), 400
    chromeInstance.delayTime(time_delay)
    return jsonify({"status": "success", "message": f"Delayed for {time_delay} seconds"}), 200

@app.route('/close_instance/<instance_id>', methods=['POST'])
def close_instance(instance_id):
    chromeInstance = None
    for c in chrome_instances:
        if c.index_chrome == int(instance_id):
            chromeInstance = c
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404
    try:
        chromeInstance.chrome.quit()
        return jsonify({"status": "success", "message": "Browser closed"}), 200
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500
    
@app.route('/check_exist_element/<instance_id>', methods=['POST'])
def check_exist_element(instance_id):
    chromeInstance = None
    for c in chrome_instances:
        if c.index_chrome == int(instance_id):
            chromeInstance = c
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404
    data = request.json
    if not data or 'selector' not in data:
        return jsonify({"error": "Missing required parameters"}), 400

    selector = data['selector']
    time_wait = data.get('time_wait', 0.0)

    if not isinstance(selector, str) or not isinstance(time_wait, (int, float)):
        return jsonify({"error": "Invalid parameter types"}), 400
    try:
        result = chromeInstance.check_exist_element(selector, time_wait)
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500
    if result == "-2":
        return jsonify({"status": "success", "message": "Chrome is close"}), 400
    else:
        return jsonify({"status": "success", "is_exist": result}), 200
    

@app.route('/check_exist_elements/<instance_id>', methods=['POST'])
def check_exist_elements(instance_id):
    chromeInstance = None
    for c in chrome_instances:
        if c.index_chrome == int(instance_id):
            chromeInstance = c
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404
    data = request.json
    if not data or 'time_out' not in data or 'selectors' not in data:
        return jsonify({"error": "Missing required parameters"}), 400
    time_out = data['time_out']
    selectors = data['selectors']
    if not isinstance(time_out, (int, float)) or not isinstance(selectors, list):
        return jsonify({"error": "Invalid parameter types"}), 400
    try:
        result = chromeInstance.check_exist_element(selectors , time_out)
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500
    if result == "-2":
        return jsonify({"status": "success", "message": "Chrome is close"}), 400
    else:
        return jsonify({"status": "success", "is_exist": result}), 200
    

@app.route('/get_url/<instance_id>', methods=['GET'])
def get_url(instance_id):
    chromeInstance = None
    for c in chrome_instances:
        if c.index_chrome == int(instance_id):
            chromeInstance = c
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404
    try:
        result = chromeInstance.get_url()
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500
    if result == "-2":
        return jsonify({"status": "error", "message": "Chrome is close"}), 400
    else:
        return jsonify({"status": "success", "url": result}), 200

@app.route('/get_attribute_value/<instance_id>', methods=['POST'])
def get_attribute_value(instance_id):
    chromeInstance = None
    for c in chrome_instances:
        if c.index_chrome == int(instance_id):
            chromeInstance = c
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404
    data = request.json
    if not data or 'selector' not in data or 'attribute_name' not in data:
        return jsonify({"error": "Missing required parameters"}), 400
    selector = data['selector']
    attribute_name = data['attribute_name']
    if not isinstance(selector, str) or not isinstance(attribute_name, str):
        return jsonify({"error": "Invalid parameter types"}), 400
    try:
        result = chromeInstance.getattribute_value(selector, attribute_name)
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500
    if result == "-2":
        return jsonify({"status": "error", "message": "Chrome is close"}), 400
    else:
        return jsonify({"status": "success", "value": result}), 200


@app.route('/find_and_click/<instance_id>', methods=['POST'])
def api_find_and_click(instance_id):
    chromeInstance = None
    for c in chrome_instances:
        if c.index_chrome == int(instance_id):
            chromeInstance = c
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404

    data = request.json
    if not data or 'time_wait_seconds' not in data or 'type_attribute' not in data or 'attribute_value' not in data:
        return jsonify({"error": "Missing required parameters"}), 400

    time_wait_seconds = data['time_wait_seconds']
    type_attribute = data['type_attribute']
    attribute_value = data['attribute_value']
    index = data.get('index', 0)
    sub_type_attribute = data.get('sub_type_attribute', 0)
    sub_attribute_value = data.get('sub_attribute_value', "")
    sub_index = data.get('sub_index', 0)

    if not all(isinstance(i, int) for i in [time_wait_seconds, type_attribute, index, sub_type_attribute, sub_index]) or \
       not all(isinstance(i, str) for i in [attribute_value, sub_attribute_value]):
        return jsonify({"error": "Invalid parameter types"}), 400

    try:
        result = chromeInstance.find_and_click(
            time_wait_seconds, type_attribute, attribute_value, index,
            sub_type_attribute, sub_attribute_value, sub_index
        )
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

    if result == -2:
        return jsonify({"status": "error", "message": "Chrome is closed"}), 400
    elif result == 0:
        return jsonify({"status": "error", "message": "Element not found or click failed"}), 404
    else:
        return jsonify({"status": "success", "message": "Element clicked successfully"}), 200


@app.route('/send_keys_with_speed/<int:instance_id>', methods=['POST'])
def api_send_keys_with_speed(instance_id):
    chromeInstance = next((c for c in chrome_instances if c.index_chrome == instance_id), None)
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404

    data = request.json
    if not data or 'toc_do' not in data or 'type_attribute' not in data or 'attribute_value' not in data or 'content' not in data or 'time_delay_second' not in data:
        return jsonify({"error": "Missing required parameters"}), 400

    toc_do = data['toc_do']
    type_attribute = data['type_attribute']
    attribute_value = data['attribute_value']
    content = data['content']
    time_delay_second = data['time_delay_second']
    is_click = data.get('is_click', True)
    time_delay_after_click = data.get('time_delay_after_click', 0.1)

    if not all(isinstance(i, (int, float)) for i in [toc_do, type_attribute, time_delay_second, time_delay_after_click]) or \
       not isinstance(attribute_value, str) or not isinstance(content, str) or not isinstance(is_click, bool):
        return jsonify({"error": "Invalid parameter types"}), 400

    try:
        result = chromeInstance.send_keys_with_speed(
            toc_do, type_attribute, attribute_value, content, time_delay_second, is_click, time_delay_after_click
        )
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

    if result == -2:
        return jsonify({"status": "error", "message": "Chrome is closed"}), 400
    elif result == 0:
        return jsonify({"status": "error", "message": "Operation failed"}), 400
    else:
        return jsonify({"status": "success", "message": "Keys sent successfully"}), 200

@app.route('/send_enter/<int:instance_id>', methods=['POST'])
def api_send_enter(instance_id):
    chromeInstance = next((c for c in chrome_instances if c.index_chrome == instance_id), None)
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404

    data = request.json
    type_attribute = data.get('type_attribute')
    attribute_value = data.get('attribute_value')
    index = data.get('index', 0)
    sub_type_attribute = data.get('sub_type_attribute', 0)
    sub_attribute_value = data.get('sub_attribute_value', '')
    sub_index = data.get('sub_index', 0)

    result = chromeInstance.send_enter(type_attribute, attribute_value, index, sub_type_attribute, sub_attribute_value, sub_index)

    if result == -2:
        return jsonify({"status": "error", "message": "Chrome is closed"}), 400
    elif result == 0:
        return jsonify({"status": "error", "message": "Failed to send Enter key"}), 400
    else:
        return jsonify({"status": "success", "message": "Enter key sent successfully"}), 200


@app.route('/send_keys/<int:instance_id>', methods=['POST'])
def send_keys(instance_id):
    chromeInstance = next((c for c in chrome_instances if c.index_chrome == instance_id), None)
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404

    data = request.json
    type_attribute = data.get('type_attribute')
    attribute_value = data.get('attribute_value')
    content = data.get('content')
    time_delay_second = data.get('time_delay_second', 0)
    is_click = data.get('is_click', True)
    time_delay_after_click = data.get('time_delay_after_click', 0.1)

    result = chromeInstance.send_keys(type_attribute, attribute_value, content, time_delay_second, is_click, time_delay_after_click)

    if result == -2:
        return jsonify({"status": "error", "message": "Chrome is closed"}), 400
    elif result == 0:
        return jsonify({"status": "error", "message": "Failed to send keys"}), 400
    else:
        return jsonify({"status": "success", "message": "Keys sent successfully"}), 200


@app.route('/send_keys_without_time_delay_second/<int:instance_id>', methods=['POST'])
def api_send_keys(instance_id):
    chrome_instance = next((c for c in chrome_instances if c.index_chrome == instance_id), None)
    if chrome_instance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404

    data = request.json
    type_attribute = data.get('type_attribute')
    attribute_value = data.get('attribute_value')
    content = data.get('content')
    is_click = data.get('is_click', True)
    time_delay_after_click = data.get('time_delay_after_click', 0.1)

    result = chrome_instance.send_keys(type_attribute, attribute_value, content, is_click, time_delay_after_click)

    if result == -2:
        return jsonify({"status": "error", "message": "Chrome is closed"}), 400
    elif result == 0:
        return jsonify({"status": "error", "message": "Failed to send keys"}), 400
    else:
        return jsonify({"status": "success", "message": "Keys sent successfully"}), 200

    
@app.route('/click_js_single/<int:instance_id>', methods=['POST'])
def api_click_js_single(instance_id):
    chromeInstance = next((c for c in chrome_instances if c.index_chrome == instance_id), None)
    
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404

    data = request.json
    css_selectors_or_xpath = data.get('selector')

    if not css_selectors_or_xpath:
        return jsonify({"status": "error", "message": "No selector provided"}), 400

    result = chromeInstance.clickJS(css_selectors_or_xpath)

    if result:
        return jsonify({"status": "success", "message": "Click JS successful"}), 200
    else:
        return jsonify({"status": "error", "message": "Click JS failed"}), 400 

@app.route('/count_element/<int:instance_id>', methods=['POST'])
def api_count_element(instance_id):
    chromeInstance = next((c for c in chrome_instances if c.index_chrome == instance_id), None)
    
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404

    data = request.json
    query_selector = data.get('selector')

    if not query_selector:
        return jsonify({"status": "error", "message": "No selector provided"}), 400

    result = chromeInstance.count_element(query_selector)

    if result == -2:
        return jsonify({"status": "error", "message": "Chrome is closed"}), 500
    else:
        return jsonify({"status": "success", "message": "Element count retrieved", "count": result}), 200

@app.route('/click_with_action/<int:instance_id>', methods=['POST'])
def api_click_with_action(instance_id):
    chromeInstance = next((c for c in chrome_instances if c.index_chrome == instance_id), None)
    
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404

    data = request.json
    type_attribute = data.get('type_attribute')
    attribute_value = data.get('attribute_value')
    index = data.get('index', 0)
    sub_type_attribute = data.get('sub_type_attribute', 0)
    sub_attribute_value = data.get('sub_attribute_value', "")
    sub_index = data.get('sub_index', 0)

    if type_attribute is None or attribute_value is None:
        return jsonify({"status": "error", "message": "Missing required parameters"}), 400

    result = chromeInstance.click_with_action(
        type_attribute, attribute_value, index, sub_type_attribute, sub_attribute_value, sub_index
    )

    if result == -2:
        return jsonify({"status": "error", "message": "Chrome is closed"}), 500
    elif result == 1:
        return jsonify({"status": "success", "message": "Click action performed successfully"}), 200
    else:
        return jsonify({"status": "error", "message": "Click action failed"}), 400

@app.route('/send_enter_short/<int:instance_id>', methods=['POST'])
def api_send_enter_short(instance_id):
    chromeInstance = next((c for c in chrome_instances if c.index_chrome == instance_id), None)
    
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404

    data = request.json
    css_selectors_or_xpath = data.get('selector')

    if not css_selectors_or_xpath:
        return jsonify({"status": "error", "message": "No selector provided"}), 400

    result = chromeInstance.send_enter(css_selectors_or_xpath)

    if result == -2:
        return jsonify({"status": "error", "message": "Chrome is closed"}), 500
    elif result == 1:
        return jsonify({"status": "success", "message": "Enter key sent successfully"}), 200
    else:
        return jsonify({"status": "error", "message": "Failed to send Enter key"}), 400


@app.route('/capture/<instance_id>', methods=['POST'])
def api_screen_capture(instance_id):
    # Find the correct Chrome instance
    chromeInstance = next((c for c in chrome_instances if c.index_chrome == int(instance_id)), None)
    
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404

    # Get parameters from the request
    data = request.json
    image_path = data.get('image_path')
    file_name = data.get('file_name')

    if not image_path or not file_name:
        return jsonify({"status": "error", "message": "Missing image_path or file_name"}), 400

    try:
        result = chromeInstance.screen_capture(image_path, file_name)
        
        if result == -2:
            return jsonify({"status": "error", "message": "Chrome is closed"}), 400
        elif result == 1:
            return jsonify({"status": "success", "message": "Screenshot captured successfully"}), 200
        else:
            return jsonify({"status": "error", "message": "Failed to capture screenshot"}), 500
    
    except Exception as e:
        print(f"An error occurred: {str(e)}")
        return jsonify({"status": "error", "message": str(e)}), 500


@app.route('/get_cookie/<instance_id>', methods=['GET'])
def api_get_cookie(instance_id):
    # Find the correct Chrome instance
    chromeInstance = next((c for c in chrome_instances if c.index_chrome == int(instance_id)), None)
    
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404

    # Get domain from query parameters, default to "facebook"
    domain = request.args.get('domain', 'facebook')

    try:
        if chromeInstance.checkChromeClose():
            return jsonify({"status": "error", "message": "Chrome is closed"}), 400

        cookie_text = chromeInstance.get_cookie(domain)
        
        if cookie_text:
            return jsonify({"status": "success", "cookie": cookie_text}), 200
        else:
            return jsonify({"status": "success", "message": "No cookies found for the specified domain"}), 200
    
    except Exception as e:
        error_message = f"An error occurred: {str(e)}"
        stack_trace = traceback.format_exc()
        chromeInstance.export_error(None, e, f"chrome.GetCookieFromChrome({domain})")
        return jsonify({"status": "error", "message": error_message, "stack_trace": stack_trace}), 500


@app.route('/get_uid/<int:instance_id>', methods=['GET'])
def api_get_uid(instance_id):
    chromeInstance = next((c for c in chrome_instances if c.index_chrome == instance_id), None)
    
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404

    uid = chromeInstance.get_uid()

    if uid:
        return jsonify({"status": "success", "uid": uid}), 200
    else:
        return jsonify({"status": "error", "message": "UID not found"}), 404


@app.route('/click_with_action_single/<int:instance_id>', methods=['POST'])
def click_with_action_api(instance_id):
    chromeInstance = next((c for c in chrome_instances if c.index_chrome == instance_id), None)
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404

    data = request.json
    css_selectors_or_xpath = data.get('css_selectors_or_xpath')

    if not css_selectors_or_xpath:
        return jsonify({"status": "error", "message": "css_selectors_or_xpath is required"}), 400

    result = chromeInstance.click_with_action(css_selectors_or_xpath)

    if result == -2:
        return jsonify({"status": "error", "message": "Chrome is closed"}), 400
    elif result == 0:
        return jsonify({"status": "error", "message": "Failed to click element"}), 400
    else:
        return jsonify({"status": "success", "message": "Element clicked successfully"}), 200


@app.route('/click_single/<int:instance_id>', methods=['POST'])
def click_single_api(instance_id):
    chromeInstance = next((c for c in chrome_instances if c.index_chrome == instance_id), None)
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404

    data = request.json
    css_selectors_or_xpath = data.get('css_selectors_or_xpath')

    if not css_selectors_or_xpath:
        return jsonify({"status": "error", "message": "css_selectors_or_xpath is required"}), 400

    result = chromeInstance.click(css_selectors_or_xpath)

    if result:
        return jsonify({"status": "success", "message": "Element clicked successfully"}), 200
    else:
        return jsonify({"status": "error", "message": "Failed to click element"}), 400


@app.route('/goto_url_if_not_exist/<instance_id>', methods=['POST'])
def goto_url_if_not_exist_api(instance_id):
    chromeInstance = next((c for c in chrome_instances if c.index_chrome == instance_id), None)
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404
    
    url = request.json.get('url')
    if not url:
        return jsonify({"status": "error", "message": "URL is required"}), 400

    try:
        result = chromeInstance.goto_url_if_not_exist(url)
        if result == 1:
            return jsonify({"status": "success", "message": "Navigated to URL"}), 200
        elif result == -2:
            return jsonify({"status": "error", "message": "Chrome is closed"}), 400
        else:
            return jsonify({"status": "error", "message": "Failed to navigate to URL"}), 500
    except Exception as e:
        print(f"An error occurred: {str(e)}")
        return jsonify({"status": "error", "message": str(e)}), 500



@app.route('/add_cookie_into_chrome/<instance_id>', methods=['POST'])
def add_cookie_into_chrome_api(instance_id):
    chrome_instance = next((c for c in chrome_instances if c.index_chrome == int(instance_id)), None)
    
    if chrome_instance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404
    
    cookie = request.json.get('cookie')
    domain = request.json.get('domain', '.facebook.com')
    
    if not cookie:
        return jsonify({"status": "error", "message": "Cookie is required"}), 400

    try:
        result = chrome_instance.add_cookie_into_chrome(cookie, domain)
        if result == 1:
            return jsonify({"status": "success", "message": "Cookie added successfully"}), 200
        elif result == -2:
            return jsonify({"status": "error", "message": "Chrome instance is not live"}), 400
        else:
            return jsonify({"status": "error", "message": "Failed to add cookie"}), 500
    except Exception as e:
        return jsonify({"status": "error", "message": str(e), "traceback": traceback.format_exc()}), 500



@app.route('/refresh/<instance_id>', methods=['GET'])
def refresh_browser(instance_id):
    chrome_instance = next((c for c in chrome_instances if c.index_chrome == int(instance_id)), None)
    
    if chrome_instance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404

    try:
        result = chrome_instance.refresh()
        if result == 1:
            return jsonify({"status": "success", "message": "Browser refreshed successfully"}), 200
        elif result == -2:
            return jsonify({"status": "error", "message": "Chrome is close"}), 400
        else:
            return jsonify({"status": "error", "message": "Failed to refresh browser"}), 500
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500



@app.route('/health', methods=['GET'])
def health_check():
    return jsonify({"status": "OK"}), 200

if __name__ == '__main__':
    app.run(debug=True)
    # Add more methods as needed for your web API