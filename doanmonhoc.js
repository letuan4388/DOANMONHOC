// JavaScript Document

var BK = "https://rawgit.com/letuan4388/DOANMONHOC/master/Logo_HCMUT.png";
var ON = "https://rawgit.com/letuan4388/DOANMONHOC/master/ON.png";
var OFF = "https://rawgit.com/letuan4388/DOANMONHOC/master/OFF.png";
var strGPIO1 = "";
var strGPIO2 = "";

function GetGPIO() {
	nocache = "&nocache=" + Math.random();
	var xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = function () {
		if (this.readyState == 4 && this.status == 200) {
			Process(this);
		}
	};
	xhttp.open("GET", strGPIO1 + strGPIO2 + nocache, true);
	xhttp.send();
	strGPIO1 = "";
	strGPIO2 = "";
}

function Process(xml) {
	var x = xml.responseXML.getElementsByTagName("GPIO");
	if (x[0].childNodes[0].nodeValue == "1")
		document.getElementById("gpio1").src = ON;
	else
		document.getElementById("gpio1").src = OFF;
	if (x[1].childNodes[0].nodeValue == "1")
		document.getElementById("gpio2").src = ON;
	else
		document.getElementById("gpio2").src = OFF;
}

function SetGPIO(value) {
	if (value == 1) {
		strGPIO1 = "GPIO1";		
	}
	if (value == 2) {
		strGPIO2 = "GPIO2";
	}
}

function myFunction() {
	document.getElementById("logo").src = BK;
	setInterval("GetGPIO()", 500);
}
