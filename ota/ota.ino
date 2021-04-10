#include <WiFi.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>

#define SSID        "A06.11"
#define PASSWORD    "tamsomot"
const char rootCACertificate[] PROGMEM = "-----BEGIN CERTIFICATE-----\n"
"MIIIajCCB1KgAwIBAgIQCQ72DuLD93utHcpFVVphrjANBgkqhkiG9w0BAQsFADBk\n"
"MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
"d3cuZGlnaWNlcnQuY29tMSMwIQYDVQQDExpEaWdpQ2VydCBCYWx0aW1vcmUgQ0Et\n"
"MiBHMjAeFw0yMDA4MjcwMDAwMDBaFw0yMTA5MDExMjAwMDBaMHsxCzAJBgNVBAYT\n"
"AlVTMRMwEQYDVQQIEwpXYXNoaW5ndG9uMRAwDgYDVQQHEwdTZWF0dGxlMRkwFwYD\n"
"VQQKExBBbWF6b24uY29tLCBJbmMuMSowKAYDVQQDDCEqLnMzLWFwLXNvdXRoZWFz\n"
"dC0xLmFtYXpvbmF3cy5jb20wggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIB\n"
"AQCvVRq+ZzwsHPiqaKDiDlr0GMN3ZN3IfpktOXUbSDfCUXpNUi4RqJ9f3R2jhcZb\n"
"rICUqnTQVK5FeCfkGZY47+cxpJn+MkDgsLux/zgMEJHiyGiFkbD+IebXgaVvEdCx\n"
"75kQK/WqP9QtS4KoKqq989J5sOr70O3z8OdV6iP12P3q4Yi2ARvPSloK+UYfQ3+v\n"
"mn5fyyE3qpSVE3rD+l7/pT7JkTY5CbpwSWGQTgyWobCOgNGyoToktXlylCDi76GJ\n"
"Ci2IDDlnbZhoTKILJojtojfdLn8c4BLSXAZ72jZTl2BsSIfdvYPdFOL0Awjeyp++\n"
"Rk28EDaYcq1CidU32qz1BC/JAgMBAAGjggT/MIIE+zAfBgNVHSMEGDAWgBTAErIo\n"
"dGhGZ+lwJXQaAEVbBn1cRDAdBgNVHQ4EFgQUiKOcbAl0fOXLIcAsfz5RsyhuXWww\n"
"ggIlBgNVHREEggIcMIICGIIfczMtYXAtc291dGhlYXN0LTEuYW1hem9uYXdzLmNv\n"
"bYIhKi5zMy1hcC1zb3V0aGVhc3QtMS5hbWF6b25hd3MuY29tgh9zMy5hcC1zb3V0\n"
"aGVhc3QtMS5hbWF6b25hd3MuY29tgiEqLnMzLmFwLXNvdXRoZWFzdC0xLmFtYXpv\n"
"bmF3cy5jb22CKXMzLmR1YWxzdGFjay5hcC1zb3V0aGVhc3QtMS5hbWF6b25hd3Mu\n"
"Y29tgisqLnMzLmR1YWxzdGFjay5hcC1zb3V0aGVhc3QtMS5hbWF6b25hd3MuY29t\n"
"ghIqLnMzLmFtYXpvbmF3cy5jb22CKSouczMtY29udHJvbC5hcC1zb3V0aGVhc3Qt\n"
"MS5hbWF6b25hd3MuY29tgidzMy1jb250cm9sLmFwLXNvdXRoZWFzdC0xLmFtYXpv\n"
"bmF3cy5jb22CMyouczMtY29udHJvbC5kdWFsc3RhY2suYXAtc291dGhlYXN0LTEu\n"
"YW1hem9uYXdzLmNvbYIxczMtY29udHJvbC5kdWFsc3RhY2suYXAtc291dGhlYXN0\n"
"LTEuYW1hem9uYXdzLmNvbYItKi5zMy1hY2Nlc3Nwb2ludC5hcC1zb3V0aGVhc3Qt\n"
"MS5hbWF6b25hd3MuY29tgjcqLnMzLWFjY2Vzc3BvaW50LmR1YWxzdGFjay5hcC1z\n"
"b3V0aGVhc3QtMS5hbWF6b25hd3MuY29tMA4GA1UdDwEB/wQEAwIFoDAdBgNVHSUE\n"
"FjAUBggrBgEFBQcDAQYIKwYBBQUHAwIwgYEGA1UdHwR6MHgwOqA4oDaGNGh0dHA6\n"
"Ly9jcmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEJhbHRpbW9yZUNBLTJHMi5jcmww\n"
"OqA4oDaGNGh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEJhbHRpbW9y\n"
"ZUNBLTJHMi5jcmwwTAYDVR0gBEUwQzA3BglghkgBhv1sAQEwKjAoBggrBgEFBQcC\n"
"ARYcaHR0cHM6Ly93d3cuZGlnaWNlcnQuY29tL0NQUzAIBgZngQwBAgIweQYIKwYB\n"
"BQUHAQEEbTBrMCQGCCsGAQUFBzABhhhodHRwOi8vb2NzcC5kaWdpY2VydC5jb20w\n"
"QwYIKwYBBQUHMAKGN2h0dHA6Ly9jYWNlcnRzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2Vy\n"
"dEJhbHRpbW9yZUNBLTJHMi5jcnQwDAYDVR0TAQH/BAIwADCCAQQGCisGAQQB1nkC\n"
"BAIEgfUEgfIA8AB1APZclC/RdzAiFFQYCDCUVo7jTRMZM7/fDC8gC8xO8WTjAAAB\n"
"dDJbFgIAAAQDAEYwRAIgGL1AhtCbKhKwMvdTtmrQegUL/POHhqj+I4PBvgfFGqcC\n"
"IFQ4/rRooH3ID5OuY3zWgmx1JS216SWG5MpO0DD99EMvAHcAXNxDkv7mq0VEsV6a\n"
"1FbmEDf71fpH3KFzlLJe5vbHDsoAAAF0MlsV/wAABAMASDBGAiEA4/XYi3FWgW/+\n"
"Pruxmu3xk4uVgxMFae8sKOHEMeFtexACIQD9Ss0pKC9X6sBlcNFw34vHnbffMS+i\n"
"2zYbEOgoKk5rYzANBgkqhkiG9w0BAQsFAAOCAQEAlczKIXu2x+xg7LHR+KcCWNoO\n"
"bZIIR9ANHKsCLkgHA11T9Y1e0hS5WPkXGXYVZVD++G4fJzzhqepOMAiCA4i3NMVo\n"
"it+Ftzz+kChninA8oYpfXBFkhrQzfWT/jAiRvO4G2+hijq6XxGM2ZCd5ye6ukNGi\n"
"PdXiWfccVQ/KLOYJxJSnTwlyhqaQQuKb2oFH8rqP21yjZLoiOfCQ5WoLlSQkGiqV\n"
"F8ypoNyEZo98Xzo5CGSGXt1XxfnEaOTEVpvQhuJvkgO8epzUR2p5GdF3XU4ogAJg\n"
"n/0+3nXLMACbqKogdRKd9oLPujNB06Rl3lLC7TCDufr6H615y8MhPGiPiU3HrQ==\n"
"-----END CERTIFICATE-----\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIEYzCCA0ugAwIBAgIQAYL4CY6i5ia5GjsnhB+5rzANBgkqhkiG9w0BAQsFADBa\n"
"MQswCQYDVQQGEwJJRTESMBAGA1UEChMJQmFsdGltb3JlMRMwEQYDVQQLEwpDeWJl\n"
"clRydXN0MSIwIAYDVQQDExlCYWx0aW1vcmUgQ3liZXJUcnVzdCBSb290MB4XDTE1\n"
"MTIwODEyMDUwN1oXDTI1MDUxMDEyMDAwMFowZDELMAkGA1UEBhMCVVMxFTATBgNV\n"
"BAoTDERpZ2lDZXJ0IEluYzEZMBcGA1UECxMQd3d3LmRpZ2ljZXJ0LmNvbTEjMCEG\n"
"A1UEAxMaRGlnaUNlcnQgQmFsdGltb3JlIENBLTIgRzIwggEiMA0GCSqGSIb3DQEB\n"
"AQUAA4IBDwAwggEKAoIBAQC75wD+AAFz75uI8FwIdfBccHMf/7V6H40II/3HwRM/\n"
"sSEGvU3M2y24hxkx3tprDcFd0lHVsF5y1PBm1ITykRhBtQkmsgOWBGmVU/oHTz6+\n"
"hjpDK7JZtavRuvRZQHJaZ7bN5lX8CSukmLK/zKkf1L+Hj4Il/UWAqeydjPl0kM8c\n"
"+GVQr834RavIL42ONh3e6onNslLZ5QnNNnEr2sbQm8b2pFtbObYfAB8ZpPvTvgzm\n"
"+4/dDoDmpOdaxMAvcu6R84Nnyc3KzkqwIIH95HKvCRjnT0LsTSdCTQeg3dUNdfc2\n"
"YMwmVJihiDfwg/etKVkgz7sl4dWe5vOuwQHrtQaJ4gqPAgMBAAGjggEZMIIBFTAd\n"
"BgNVHQ4EFgQUwBKyKHRoRmfpcCV0GgBFWwZ9XEQwHwYDVR0jBBgwFoAU5Z1ZMIJH\n"
"WMys+ghUNoZ7OrUETfAwEgYDVR0TAQH/BAgwBgEB/wIBADAOBgNVHQ8BAf8EBAMC\n"
"AYYwNAYIKwYBBQUHAQEEKDAmMCQGCCsGAQUFBzABhhhodHRwOi8vb2NzcC5kaWdp\n"
"Y2VydC5jb20wOgYDVR0fBDMwMTAvoC2gK4YpaHR0cDovL2NybDMuZGlnaWNlcnQu\n"
"Y29tL09tbmlyb290MjAyNS5jcmwwPQYDVR0gBDYwNDAyBgRVHSAAMCowKAYIKwYB\n"
"BQUHAgEWHGh0dHBzOi8vd3d3LmRpZ2ljZXJ0LmNvbS9DUFMwDQYJKoZIhvcNAQEL\n"
"BQADggEBAC/iN2bDGs+RVe4pFPpQEL6ZjeIo8XQWB2k7RDA99blJ9Wg2/rcwjang\n"
"B0lCY0ZStWnGm0nyGg9Xxva3vqt1jQ2iqzPkYoVDVKtjlAyjU6DqHeSmpqyVDmV4\n"
"7DOMvpQ+2HCr6sfheM4zlbv7LFjgikCmbUHY2Nmz+S8CxRtwa+I6hXsdGLDRS5rB\n"
"bxcQKegOw+FUllSlkZUIII1pLJ4vP1C0LuVXH6+kc9KhJLsNkP5FEx2noSnYZgvD\n"
"0WyzT7QrhExHkOyL4kGJE7YHRndC/bseF/r/JUuOUFfrjsxOFT+xJd1BDKCcYm1v\n"
"upcHi9nzBhDFKdT3uhaQqNBU4UtJx5g=\n"
"-----END CERTIFICATE-----\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDdzCCAl+gAwIBAgIEAgAAuTANBgkqhkiG9w0BAQUFADBaMQswCQYDVQQGEwJJ\n"
"RTESMBAGA1UEChMJQmFsdGltb3JlMRMwEQYDVQQLEwpDeWJlclRydXN0MSIwIAYD\n"
"VQQDExlCYWx0aW1vcmUgQ3liZXJUcnVzdCBSb290MB4XDTAwMDUxMjE4NDYwMFoX\n"
"DTI1MDUxMjIzNTkwMFowWjELMAkGA1UEBhMCSUUxEjAQBgNVBAoTCUJhbHRpbW9y\n"
"ZTETMBEGA1UECxMKQ3liZXJUcnVzdDEiMCAGA1UEAxMZQmFsdGltb3JlIEN5YmVy\n"
"VHJ1c3QgUm9vdDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKMEuyKr\n"
"mD1X6CZymrV51Cni4eiVgLGw41uOKymaZN+hXe2wCQVt2yguzmKiYv60iNoS6zjr\n"
"IZ3AQSsBUnuId9Mcj8e6uYi1agnnc+gRQKfRzMpijS3ljwumUNKoUMMo6vWrJYeK\n"
"mpYcqWe4PwzV9/lSEy/CG9VwcPCPwBLKBsua4dnKM3p31vjsufFoREJIE9LAwqSu\n"
"XmD+tqYF/LTdB1kC1FkYmGP1pWPgkAx9XbIGevOF6uvUA65ehD5f/xXtabz5OTZy\n"
"dc93Uk3zyZAsuT3lySNTPx8kmCFcB5kpvcY67Oduhjprl3RjM71oGDHweI12v/ye\n"
"jl0qhqdNkNwnGjkCAwEAAaNFMEMwHQYDVR0OBBYEFOWdWTCCR1jMrPoIVDaGezq1\n"
"BE3wMBIGA1UdEwEB/wQIMAYBAf8CAQMwDgYDVR0PAQH/BAQDAgEGMA0GCSqGSIb3\n"
"DQEBBQUAA4IBAQCFDF2O5G9RaEIFoN27TyclhAO992T9Ldcw46QQF+vaKSm2eT92\n"
"9hkTI7gQCvlYpNRhcL0EYWoSihfVCr3FvDB81ukMJY2GQE/szKN+OMY3EU/t3Wgx\n"
"jkzSswF07r51XgdIGn9w/xZchMB5hbgF/X++ZRGjD8ACtPhSNzkE1akxehi/oCr0\n"
"Epn3o0WC4zxe9Z2etciefC7IpJ5OCBRLbf1wbWsaY71k5h+3zvDyny67G7fyUIhz\n"
"ksLi4xaNmjICq44Y3ekQEe5+NauQrz4wlHrQMz2nZQ/1/I6eYs9HRCwBXbsdtTLS\n"
"R9I4LtD+gdwyah617jzV/OeBHRnDJELqYzmp\n"
"-----END CERTIFICATE-----\n";

void updateFirmware(String url)
{
  WiFiClientSecure client;
  client.setCACert(rootCACertificate);
  client.setTimeout(12000 / 1000);
  httpUpdate.setLedPin(2, HIGH);
  Serial.println("Uploading..");
  Serial.println("Led at pin 2 should be blinking representing code download speed");
  
  t_httpUpdate_return ret = httpUpdate.update(client, url);

  switch (ret)
  {
  case HTTP_UPDATE_FAILED:
    Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
    break;
  case HTTP_UPDATE_NO_UPDATES:
    Serial.println("HTTP_UPDATE_NO_UPDATES");
    break;
  case HTTP_UPDATE_OK:
    Serial.println("HTTP_UPDATE_OK");
    break;
  }
}

void m_connect_wifi()
{
  Serial.print("Connecting as wifi client to ");
  Serial.println(SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  WiFi.waitForConnectResult();
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else
  {
    Serial.println("Unable to connect");
  }
}

void setup()
{
  Serial.begin(9600);
  m_connect_wifi();
  updateFirmware("https://f0150-toybox.s3-ap-southeast-1.amazonaws.com/SerialEvent.ino.bin");
}

void loop()
{
  // put your main code here, to run repeatedly:
}
