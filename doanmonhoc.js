// JavaScript Document

var strGPIO1 = "";
var strGPIO2 = "";
var GPIO1 = 0;
var GPIO2 = 0;

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
		document.getElementById("gpio1").innerHTML = "BẬT";
	else
		document.getElementById("gpio1").innerHTML = "TẮT";
	if (x[1].childNodes[0].nodeValue == "1")
		document.getElementById("gpio2").innerHTML = "BẬT";
	else
		document.getElementById("gpio2").innerHTML = "TẮT";
}

function SetGPIO(value) {
	if (value == 1) {
		strGPIO1 = "GPIO1";
		GPIO1 = 1 - GPIO1;
	}
	if (value == 2) {
		strGPIO2 = "GPIO2";
		GPIO2 = 1 - GPIO2;
	}
	if (GPIO1 == 1)
		document.getElementById("gpio1").innerHTML = "BẬT";
	else
		document.getElementById("gpio1").innerHTML = "TẮT";
	if (GPIO2 == 1)
		document.getElementById("gpio2").innerHTML = "BẬT";
	else
		document.getElementById("gpio2").innerHTML = "TẮT";
}

function myFunction() {
	setInterval("GetGPIO()", 500);
}