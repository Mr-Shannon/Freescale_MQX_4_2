	var hvac_value = new Array(7);
	var rtc_value = new Array(3);
	var data_received = 0;
	// header.js
  
	sfHover2 = function() {
		var navthree = document.getElementById("lnv");
		if (navthree) {
			var sfEls2 = document.getElementById("lnv").getElementsByTagName("LI");
			for ( var i = 0; i < sfEls2.length; i++) {
				sfEls2[i].onmouseover = function() {
					this.className += " sfhover";
					hideselects('hidden');
				}
				sfEls2[i].onmouseout = function() {
					this.className = this.className.replace(new RegExp(" sfhover\\b"), "");
					hideselects('visible');
				}
			}
		}
	}

	if (window.attachEvent) {
		window.attachEvent("onload", sfHover2);
	}

	function hideselects(state) {
		for (i = 0; i < document.forms.length; i++) { // if there are forms on the page
			frm = document.forms[i];
			var inputs = frm.getElementsByTagName("SELECT");
			for (j = 0; j < inputs.length; j++) {
				inputs[j].style.visibility = state;
			}
		}
	}

	// request.js

	function makeRequest(url, fn) {
		var http_request = false;

		url = url + "?sid=" + Math.random();

		data_received = 1;
		if (window.XMLHttpRequest) { // Mozilla, Safari,...
			http_request = new XMLHttpRequest();
			if (http_request.overrideMimeType) {
				http_request.overrideMimeType('text/xml');
			}
		} else if (window.ActiveXObject) { // IE
			try {
				http_request = new ActiveXObject("Msxml2.XMLHTTP");
			} catch (e) {
				try {
					http_request = new ActiveXObject("Microsoft.XMLHTTP");
				} catch (e) {
				}
			}
		}

		if (!http_request) {
			alert('Giving up :( Cannot create an XMLHTTP instance');
			return false;
		}

		http_request.onreadystatechange = function() {
			fn(http_request);
		};
		http_request.open('GET', url, true);
		http_request.send(null);
	}

	function alertContents(http_request) {
		if ((http_request.readyState == 4) && (http_request.status == 200)) {
			parse_vars(http_request.responseText);
		}
		data_received = 0;
	}
	
	function refreshUSBStatus(http_request) {
		if ((http_request.readyState == 4) && (http_request.status == 200)) {
			var visibility = http_request.responseText.split("\n");
			if (visibility.length > 0) {
				document.getElementById("usbstick").style.visibility = visibility[0];
			} else {
				document.getElementById("usbstick").style.visibility = "hidden";
			}
		}
		data_received = 0;
	}
  
	function loop() {
		if (!data_received) {
			makeRequest("usbstat.cgi", refreshUSBStatus);
		}
		setTimeout("loop()", 1000);
	}