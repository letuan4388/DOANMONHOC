#ifndef LIB_WEB_H_
#define LIB_WEB_H_

static char website[] =
"HTTP/1.1 200 OK\r\n"           
"Content-Type: text/html\r\n"
"Pragma: no-cache\r\n\r\n"
"<!doctype html>"
"<html>"
"<head>"
"<meta http-equiv='Content-Type' content='text/html; charset=utf-8' />"
"<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
"<title>CONTROL DEVICE</title>"
"</head>"
"<body onload='myFunction()' style='text-align:center'>"
"<h1>INTERNET CONTROL DEVICE</h1>"
"<button style='font-size:20px' id='gpio1' onclick='SetGPIO(1)'>THIET BI 1 DANG TAT</button>"
"<br /><br />"
"<button style='font-size:20px' id='gpio2' onclick='SetGPIO(2)'>THIET BI 2 DANG TAT</button>"
"<script src='https://rawgit.com/letuan4388/Source-Web/master/project_ajax_03.js'></script>"
"</body>"
"</html>";

#endif /* LIB_WEB_H_ */
