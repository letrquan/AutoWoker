import random
import psutil
import os
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
    
app = Flask(__name__)
chrome_instances = []

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
              return jsonify({"status": "error", "message": "Instance already exists"}), 400
        chrome_instances.append(chrome_instance)
        return jsonify({"status": "success", "instance_id": index_chrome}), 200

    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

@app.route('/open/<instance_id>', methods=['POST'])
def open_browser(instance_id):
    chromeInstance = None
    for c in chrome_instances:
        if c.index_chrome == int(instance_id):
            chromeInstance = c
            break
    if chromeInstance is None:
        return jsonify({"status": "error", "message": "Instance not found"}), 404
    try:
        chromeInstance.open()
        return jsonify({"status": "success", "message": "Browser opened"}), 200
    except Exception as e:
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
    if result:
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
        return jsonify({"status": "error", "message": "Instance not found"}), 404
    result = chromeInstance.checkChromeClose()
    return jsonify({"status": "success", "is_closed": result}), 200

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
    
@app.route('/health', methods=['GET'])
def health_check():
    return jsonify({"status": "OK"}), 200

if __name__ == '__main__':
    app.run(debug=True)
    # Add more methods as needed for your web API