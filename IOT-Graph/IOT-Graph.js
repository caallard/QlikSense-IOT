/*
 * @license    IOT-Gaph : Copyright (c) 2019, Charles-Alban Allard All rights reserved.
 * @release    1.0
 * @details    https://github.com/caallard/QlikSense-IOT
*/

define( ["qlik", "jquery", "text!./style.css"], function ( qlik, $, cssContent ) {
	'use strict';
	$( "<style>" ).html( cssContent ).appendTo( "head" );
	return {
		initialProperties: {
		},
		definition: {
			type: "items",
			component: "accordion",
			items: {
				measures : {
					uses : "measures",
					min: 1,
					max: 2
				},
				settings: {
					uses: "settings",
					items: {
						Details: {
							type: "items",
							label: "Paramètres",
							items: {
								ip: {
										type: "string",
										label: "Ip of the IOT",
										ref: "params.ip",
										defaultValue: "192.168.0.10"
								}
							}
						}
					}
				}
			}
		},
		support : {
			snapshot: true,
			export: true,
			exportData : false
		},
		paint: function ( $element,layout ) {
			console.log('--' );
			console.log('qGrandTotalRow',layout.qHyperCube.qGrandTotalRow);
			console.log('qMeasureInfo',layout.qHyperCube.qMeasureInfo);
			
			var self = this, html = "<div class='container'><div class='circle-container'>", json="[";
			var nb_diode=24
			for (var i = 0; i < nb_diode; i++) {
				
				var angle = Math.round(i*360/nb_diode)+90;
				var rotate = "transform: rotate("+angle+"deg) translate(100px);";
				
				if((i-1)<= layout.qHyperCube.qGrandTotalRow[0].qNum*nb_diode ){
					
					var red=Math.round(255-(255*(i/nb_diode)));
					var green=Math.round(0+(255*(i/nb_diode)));
					var blue=0;
					
					if(red<0){
						red=0;
					}else if(red>255){
						red=255;
					}
					
					if(green<0){
						green=0;
					}else if(green>255){
						green=255;
					}
					
					
					if(blue<0){
						blue=0;
					}else if(blue>255){
						blue=255;
					}
					json += "["+red+","+green+","+blue+"],";
					
					
					html += "<div style='background-color:rgb("+red+","+green+","+blue+");width:20px;height:20px;display:block; float:left; "+rotate+" '></div>"
					
					//json += "[127,0,127],";
				}else{
					html += "<div style='background-color:rgb(230,230,230);width:20px;height:20px;display:block; float:left; "+rotate+" '></div>"
					json += "[0,0,0],";
				}
			}
			json += "]";
			html += "</div><iframe src='http://"+layout.params.ip+"/update?data="+json+"' style='width: 250px; height: 45px;border: 0; display:none;'></iframe> </div>";
			$element.html( html );
		}
	};
} );
