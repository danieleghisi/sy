{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 7,
			"minor" : 3,
			"revision" : 0,
			"architecture" : "x64",
			"modernui" : 1
		}
,
		"rect" : [ 547.0, 100.0, 786.0, 429.0 ],
		"bgcolor" : [ 0.941176, 0.941176, 0.941176, 1.0 ],
		"bglocked" : 0,
		"openinpresentation" : 1,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 1,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 1,
		"objectsnaponopen" : 1,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"lefttoolbarpinned" : 0,
		"toptoolbarpinned" : 0,
		"righttoolbarpinned" : 0,
		"bottomtoolbarpinned" : 0,
		"toolbars_unpinned_last_save" : 0,
		"tallnewobj" : 0,
		"boxanimatetime" : 200,
		"enablehscroll" : 0,
		"enablevscroll" : 0,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"style" : "",
		"subpatcher_template" : "",
		"boxes" : [ 			{
				"box" : 				{
					"id" : "obj-30",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 285.0, 970.0, 246.0, 22.0 ],
					"style" : "",
					"text" : "presentation_rect -402. 119.327866 170. 69."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-17",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 33.0, 970.0, 242.0, 22.0 ],
					"style" : "",
					"text" : "presentation_rect 402. 119.327866 170. 69."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-5",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 33.0, 941.0, 60.0, 22.0 ],
					"style" : "",
					"text" : "loadbang"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"bubbleside" : 3,
					"fontname" : "Arial",
					"fontsize" : 17.491674,
					"id" : "obj-4",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 33.0, 1009.0, 422.0, 30.0 ],
					"presentation" : 1,
					"presentation_linecount" : 3,
					"presentation_rect" : [ 402.0, 119.327866, 170.0, 69.0 ],
					"style" : "",
					"text" : "Click on a module name to know more about it!",
					"textcolor" : [ 0.25, 0.25, 0.25, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-34",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "" ],
					"patching_rect" : [ 269.0, 869.0, 36.0, 22.0 ],
					"style" : "",
					"text" : "sel 1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-33",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "int", "int" ],
					"patching_rect" : [ 269.0, 839.0, 50.0, 22.0 ],
					"style" : "",
					"text" : "change"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-31",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 164.0, 846.0, 50.0, 22.0 ],
					"style" : "",
					"text" : "62 23"
				}

			}
, 			{
				"box" : 				{
					"bgtransparent" : 1,
					"border" : 0,
					"id" : "obj-22",
					"maxclass" : "lcd",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "list", "list", "int", "" ],
					"patching_rect" : [ 223.0, 803.0, 88.0, 32.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 10.0, 328.0, 88.0, 32.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-20",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 390.0, 1114.0, 37.0, 22.0 ],
					"style" : "",
					"text" : "open"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-16",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 390.0, 1147.0, 53.0, 22.0 ],
					"style" : "",
					"text" : "pcontrol"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-14",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 7,
							"minor" : 3,
							"revision" : 0,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"rect" : [ 361.0, 79.0, 783.0, 488.0 ],
						"bgcolor" : [ 0.941176, 0.941176, 0.941176, 1.0 ],
						"bglocked" : 0,
						"openinpresentation" : 1,
						"default_fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 1,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 1,
						"objectsnaponopen" : 1,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"lefttoolbarpinned" : 0,
						"toptoolbarpinned" : 0,
						"righttoolbarpinned" : 0,
						"bottomtoolbarpinned" : 0,
						"toolbars_unpinned_last_save" : 0,
						"tallnewobj" : 0,
						"boxanimatetime" : 200,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"style" : "",
						"subpatcher_template" : "",
						"boxes" : [ 							{
								"box" : 								{
									"id" : "obj-10",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 142.0, 114.0, 72.0, 22.0 ],
									"style" : "",
									"text" : "loadmess 0"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-9",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"patching_rect" : [ 15.0, 111.0, 43.0, 22.0 ],
									"style" : "",
									"text" : "* -400"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-7",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 32.0, 149.0, 74.0, 22.0 ],
									"style" : "",
									"text" : "offset 0 $1"
								}

							}
, 							{
								"box" : 								{
									"bgmode" : 0,
									"border" : 0,
									"clickthrough" : 0,
									"embed" : 1,
									"enablehscroll" : 0,
									"enablevscroll" : 0,
									"id" : "obj-4",
									"lockeddragscroll" : 0,
									"maxclass" : "bpatcher",
									"numinlets" : 1,
									"numoutlets" : 0,
									"offset" : [ 0.0, -1200.0 ],
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 7,
											"minor" : 3,
											"revision" : 0,
											"architecture" : "x64",
											"modernui" : 1
										}
,
										"rect" : [ 368.0, 171.0, 774.0, 377.0 ],
										"bglocked" : 0,
										"openinpresentation" : 0,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 1,
										"gridsize" : [ 15.0, 15.0 ],
										"gridsnaponopen" : 1,
										"objectsnaponopen" : 1,
										"statusbarvisible" : 2,
										"toolbarvisible" : 1,
										"lefttoolbarpinned" : 0,
										"toptoolbarpinned" : 0,
										"righttoolbarpinned" : 0,
										"bottomtoolbarpinned" : 0,
										"toolbars_unpinned_last_save" : 0,
										"tallnewobj" : 0,
										"boxanimatetime" : 200,
										"enablehscroll" : 1,
										"enablevscroll" : 1,
										"devicewidth" : 0.0,
										"description" : "",
										"digest" : "",
										"tags" : "",
										"style" : "",
										"subpatcher_template" : "",
										"boxes" : [ 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"hidden" : 1,
													"id" : "obj-58",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 163.0, 1428.0, 87.0, 23.0 ],
													"style" : "",
													"text" : "loadmess set"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-59",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 552.25, 1407.0, 78.0, 23.0 ],
													"style" : "",
													"text" : "loadmess X"
												}

											}
, 											{
												"box" : 												{
													"bubble" : 1,
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-60",
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 413.25, 1368.0, 262.0, 25.0 ],
													"style" : "",
													"text" : "Try this with different \"listout\" attributes"
												}

											}
, 											{
												"box" : 												{
													"fontsize" : 13.0,
													"id" : "obj-61",
													"linecount" : 2,
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 502.25, 1479.0, 173.0, 38.0 ],
													"style" : "",
													"text" : "\"GeoXge Harrison is not George Martin\""
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-62",
													"maxclass" : "newobj",
													"numinlets" : 3,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 502.25, 1439.0, 69.0, 23.0 ],
													"style" : "",
													"text" : "sy.subs 4"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-63",
													"linecount" : 2,
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 256.25, 1479.0, 173.0, 38.0 ],
													"style" : "",
													"text" : "\"Mrn HnaGioo irrotGrtgreoeseea   nsig\""
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-65",
													"linecount" : 2,
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 20.5, 1479.0, 194.0, 38.0 ],
													"style" : "",
													"text" : "\"fooGeorge Harrison\" is not \"George Martin\""
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-66",
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 157.0, 1368.0, 246.0, 23.0 ],
													"style" : "",
													"text" : "\"George Harrison\" is not \"George Martin\""
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-67",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 256.25, 1439.0, 79.0, 23.0 ],
													"style" : "",
													"text" : "sy.scramble"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-68",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 20.5, 1439.0, 98.0, 23.0 ],
													"style" : "",
													"text" : "sy.prepend foo"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-69",
													"linecount" : 3,
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 16.0, 1212.0, 750.0, 50.0 ],
													"style" : "",
													"text" : "The \"listout\" attribute handles whether a module output should be sent out as a single symbol (0), or split as much as possible into different atoms whenever whitespaces are found (2), or if (which is the default, 1) lists are only output in accordance with the incoming elements, i.e., roughly speaking, lists are output only whenever they match incoming lists."
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-70",
													"linecount" : 4,
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 39.0, 1292.0, 782.0, 65.0 ],
													"style" : "",
													"text" : "- \"Always As Single Symbol\": the object output is always wrapped as a single symbol\n- \"Adapt To Input\" (default): lists are only output in accordance with the incoming elements; \n   roughly speaking, lists are output only whenever they match incoming lists.\n- \"Always Separate\": force deparsing of outgoing data into different atoms, whenever spaces are found.",
													"textcolor" : [ 0.5, 0.5, 0.5, 1.0 ]
												}

											}
, 											{
												"box" : 												{
													"attr" : "listout",
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-71",
													"maxclass" : "attrui",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 20.5, 1267.0, 322.0, 23.0 ],
													"style" : ""
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"hidden" : 1,
													"id" : "obj-55",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 163.0, 1012.0, 87.0, 23.0 ],
													"style" : "",
													"text" : "loadmess set"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-40",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 552.25, 991.0, 78.0, 23.0 ],
													"style" : "",
													"text" : "loadmess X"
												}

											}
, 											{
												"box" : 												{
													"bubble" : 1,
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-84",
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 321.0, 952.0, 262.0, 25.0 ],
													"style" : "",
													"text" : "Try this with different \"listin\" attributes"
												}

											}
, 											{
												"box" : 												{
													"fontsize" : 13.0,
													"id" : "obj-82",
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 502.25, 1063.0, 173.0, 23.0 ],
													"style" : ""
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-83",
													"maxclass" : "newobj",
													"numinlets" : 3,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 502.25, 1023.0, 69.0, 23.0 ],
													"style" : "",
													"text" : "sy.subs 4"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-81",
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 256.25, 1063.0, 173.0, 23.0 ],
													"style" : ""
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-80",
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 20.5, 1063.0, 194.0, 23.0 ],
													"style" : ""
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-77",
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 157.0, 952.0, 153.0, 23.0 ],
													"style" : "",
													"text" : "John George Paul Ringo"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-75",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 256.25, 1023.0, 79.0, 23.0 ],
													"style" : "",
													"text" : "sy.scramble"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-74",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 20.5, 1023.0, 98.0, 23.0 ],
													"style" : "",
													"text" : "sy.prepend foo"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-56",
													"linecount" : 2,
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 16.0, 811.0, 731.0, 36.0 ],
													"style" : "",
													"text" : "The \"listin\" attribute handles how lists should be processed when input. Typically you might want to treat the list as a whole, and process it globally (0), or process it element-wise (1)."
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-57",
													"linecount" : 2,
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 39.0, 891.0, 782.0, 36.0 ],
													"style" : "",
													"text" : "- \"Process Globally\": the list is treated as a whole, and processed globally \n- \"Process Element-wise\": elements are processed one by one, and then re-assembled.",
													"textcolor" : [ 0.5, 0.5, 0.5, 1.0 ]
												}

											}
, 											{
												"box" : 												{
													"attr" : "listin",
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-64",
													"maxclass" : "attrui",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 20.5, 866.0, 322.0, 23.0 ],
													"style" : ""
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"hidden" : 1,
													"id" : "obj-54",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 16.0, 707.0, 88.0, 23.0 ],
													"style" : "",
													"text" : "loadmess set"
												}

											}
, 											{
												"box" : 												{
													"hidden" : 1,
													"id" : "obj-53",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 403.0, 1887.0, 81.0, 22.0 ],
													"style" : "",
													"text" : "loadmess set"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-52",
													"linecount" : 2,
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 16.0, 1921.0, 735.0, 36.0 ],
													"style" : "",
													"text" : "The locale is a concept fully inherited by the ICU, please refer to http://userguide.icu-project.org/locale for more information. \nA locale explorer can be found here: http://demo.icu-project.org/icu-bin/locexp"
												}

											}
, 											{
												"box" : 												{
													"bubble" : 1,
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-41",
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 407.75, 1843.5, 160.0, 25.0 ],
													"style" : "",
													"text" : "Sort with Danish locale"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-46",
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 266.0, 1880.0, 92.0, 23.0 ],
													"style" : ""
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-48",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 2,
													"outlettype" : [ "", "" ],
													"patching_rect" : [ 293.25, 1845.0, 118.0, 23.0 ],
													"style" : "",
													"text" : "sy.sort @locale da"
												}

											}
, 											{
												"box" : 												{
													"fontsize" : 13.0,
													"id" : "obj-49",
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 115.000015, 1880.0, 92.0, 23.0 ],
													"style" : ""
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-50",
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 170.0, 1811.0, 99.0, 23.0 ],
													"style" : "",
													"text" : "Ångstrom Zoe"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-51",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 2,
													"outlettype" : [ "", "" ],
													"patching_rect" : [ 170.0, 1845.0, 51.0, 23.0 ],
													"style" : "",
													"text" : "sy.sort"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-39",
													"linecount" : 12,
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 16.0, 1642.0, 727.0, 181.0 ],
													"style" : "",
													"text" : "A locale identifies a specific user community - a group of users who have similar culture and language expectations for human-computer interaction (and the kinds of data they process). The languages are specified using a two- or three-letter lowercase code for a particular language. For example, Spanish is \"es\", English is \"en\" and French is \"fr\". The two-letter language code uses the ISO-639 standard.\nThe optional four-letter script code follows the language code. If specified, it should be a valid script code as  listed on the Unicode ISO 15924 Registry. There are often different language conventions within the same language. For example, Spanish is spoken in many countries in Central  and South America but the currencies are different in each country. To allow for these differences among specific geographical, political, or cultural regions, locales are specified by two-letter, uppercase codes. For example, \"ES\" represents Spain and \"MX\" represents Mexico. The two letter country code uses the ISO-3166 standard. \nLocale is crucial when you need to perform operations such as sorting, comparing, finding... For instance, in Danish the \"Å\" letter comes after \"Z\":",
													"textcolor" : [ 0.5, 0.5, 0.5, 1.0 ]
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-38",
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 16.0, 1619.0, 731.0, 21.0 ],
													"style" : "",
													"text" : "The \"locale\" attribute sets the desired locale."
												}

											}
, 											{
												"box" : 												{
													"hidden" : 1,
													"id" : "obj-37",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 2,
													"outlettype" : [ "", "" ],
													"patching_rect" : [ 918.0, 56.0, 69.0, 22.0 ],
													"save" : [ "#N", "thispatcher", ";", "#Q", "end", ";" ],
													"style" : "",
													"text" : "thispatcher"
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"hidden" : 1,
													"id" : "obj-36",
													"maxclass" : "inlet",
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 918.0, 16.0, 30.0, 30.0 ],
													"style" : ""
												}

											}
, 											{
												"box" : 												{
													"bubble" : 1,
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-35",
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 299.5, 588.0, 260.0, 25.0 ],
													"style" : "",
													"text" : "Try this with different \"numout\" attributes"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-34",
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 16.0, 408.0, 731.0, 21.0 ],
													"style" : "",
													"text" : "The \"numout\" attribute handles if and when atoms (after having been processed) should be converted to numbers."
												}

											}
, 											{
												"box" : 												{
													"bubble" : 1,
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-27",
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 240.5, 201.0, 252.0, 25.0 ],
													"style" : "",
													"text" : "Try this with different \"numin\" attributes"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-12",
													"linecount" : 3,
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 46.0, 77.0, 720.0, 50.0 ],
													"style" : "",
													"text" : "- \"Let through\": numbers are not processed, and simply let through as they are\n- \"Convert To Symbol\" (default): numbers are immediately converted to symbols, and then processed as ordinary symbols.\n- \"Drop\": numbers are ignored and dropped from the input list",
													"textcolor" : [ 0.5, 0.5, 0.5, 1.0 ]
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-8",
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 16.0, 12.0, 731.0, 21.0 ],
													"style" : "",
													"text" : "The \"numin\" attribute sets the way number should be handled when received as input (either as single atoms, or inside a list):"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-31",
													"linecount" : 5,
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 39.0, 467.0, 718.0, 79.0 ],
													"style" : "",
													"text" : "- \"Only With Numeric Original\" doesn't even try to convert: it only outputs numbers if they were already parsed as numbers, e.g. if you had set @numin to \"Let Through\".\n- \"Convert From Numeric Symbols\" (default): only converts to number those symbols that were already detected to represent a number (e.g. it'll convert \"12\" but not \"b12\")\n- \"Convert From All Symbols\" will force the conversion from any type of symbol.",
													"textcolor" : [ 0.5, 0.5, 0.5, 1.0 ]
												}

											}
, 											{
												"box" : 												{
													"bubble" : 1,
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-25",
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 353.25, 442.0, 326.0, 25.0 ],
													"style" : "",
													"text" : "Do we want to try to convert the output to numbers?"
												}

											}
, 											{
												"box" : 												{
													"bubble" : 1,
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-23",
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 243.5, 550.5, 342.0, 25.0 ],
													"style" : "",
													"text" : "Maximum number of decimal digits for float conversion"
												}

											}
, 											{
												"box" : 												{
													"attr" : "maxdecimals",
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-21",
													"maxclass" : "attrui",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 38.0, 550.5, 196.0, 23.0 ],
													"style" : "",
													"text_width" : 140.5
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-13",
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 42.75, 744.0, 57.0, 23.0 ],
													"style" : ""
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-11",
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 82.0, 643.0, 32.0, 23.0 ],
													"style" : "",
													"text" : "1"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-9",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 80.75, 707.0, 120.0, 23.0 ],
													"style" : "",
													"text" : "sy.join 1 @numin 0"
												}

											}
, 											{
												"box" : 												{
													"attr" : "numout",
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-47",
													"maxclass" : "attrui",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 20.5, 442.0, 322.0, 23.0 ],
													"style" : ""
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-42",
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 365.25, 744.0, 148.0, 23.0 ],
													"style" : ""
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-43",
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 526.25, 643.0, 32.0, 23.0 ],
													"style" : "",
													"text" : "2s"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-44",
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 417.25, 643.0, 44.0, 23.0 ],
													"style" : "",
													"text" : "1.123"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-45",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 417.25, 707.0, 128.0, 23.0 ],
													"style" : "",
													"text" : "sy.join 2"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-33",
													"maxclass" : "button",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "bang" ],
													"patching_rect" : [ 266.5, 588.0, 24.0, 24.0 ],
													"style" : ""
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-30",
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 192.0, 744.0, 57.0, 23.0 ],
													"style" : ""
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-29",
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 277.5, 643.0, 32.0, 23.0 ],
													"style" : "",
													"text" : "2"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-28",
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 230.0, 643.0, 32.0, 23.0 ],
													"style" : "",
													"text" : "1"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-26",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 230.0, 707.0, 67.0, 23.0 ],
													"style" : "",
													"text" : "sy.join 2"
												}

											}
, 											{
												"box" : 												{
													"bubble" : 1,
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-7",
													"linecount" : 2,
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 266.5, 147.0, 216.0, 40.0 ],
													"style" : "",
													"text" : "Maximum number of decimal digits for float conversion"
												}

											}
, 											{
												"box" : 												{
													"attr" : "maxdecimals",
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-5",
													"maxclass" : "attrui",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 61.0, 155.5, 196.0, 23.0 ],
													"style" : "",
													"text_width" : 140.5
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"hidden" : 1,
													"id" : "obj-2",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 20.5, 283.0, 88.0, 23.0 ],
													"style" : "",
													"text" : "loadmess set"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-24",
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 443.5, 346.0, 166.0, 23.0 ],
													"style" : ""
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-22",
													"maxclass" : "button",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "bang" ],
													"patching_rect" : [ 540.25, 196.0, 24.0, 24.0 ],
													"style" : ""
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-17",
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 542.75, 260.0, 97.0, 23.0 ],
													"style" : "",
													"text" : "\"21 or Density\""
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-18",
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 642.0, 260.0, 46.0, 23.0 ],
													"style" : "",
													"text" : "\"21.5\""
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-19",
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 443.5, 260.0, 54.0, 23.0 ],
													"style" : "",
													"text" : "Density"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-20",
													"maxclass" : "newobj",
													"numinlets" : 3,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 443.5, 301.0, 218.0, 23.0 ],
													"style" : "",
													"text" : "sy.join 3"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-16",
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 230.0, 245.0, 90.0, 23.0 ],
													"style" : "",
													"text" : "21 or Density"
												}

											}
, 											{
												"box" : 												{
													"bubble" : 1,
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-15",
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 566.25, 196.0, 163.0, 25.0 ],
													"style" : "",
													"text" : "See the difference"
												}

											}
, 											{
												"box" : 												{
													"id" : "obj-14",
													"maxclass" : "button",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "bang" ],
													"patching_rect" : [ 214.5, 201.0, 24.0, 24.0 ],
													"style" : ""
												}

											}
, 											{
												"box" : 												{
													"bubble" : 1,
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-32",
													"linecount" : 2,
													"maxclass" : "comment",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 290.0, 35.0, 197.0, 40.0 ],
													"style" : "",
													"text" : "What to do when numbers are introduced as input?"
												}

											}
, 											{
												"box" : 												{
													"attr" : "numin",
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-10",
													"maxclass" : "attrui",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 16.0, 43.5, 266.0, 23.0 ],
													"style" : ""
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-6",
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 31.5, 346.0, 262.0, 23.0 ],
													"style" : ""
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-4",
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 332.5, 245.0, 36.0, 23.0 ],
													"style" : "",
													"text" : "21.5"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-3",
													"maxclass" : "message",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 143.5, 245.0, 54.0, 23.0 ],
													"style" : "",
													"text" : "Density"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-1",
													"maxclass" : "newobj",
													"numinlets" : 3,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 127.5, 301.0, 224.0, 23.0 ],
													"style" : "",
													"text" : "sy.join 3"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"destination" : [ "obj-6", 1 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-1", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-1", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"midpoints" : [ 25.5, 254.75, 137.0, 254.75 ],
													"source" : [ "obj-10", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-9", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-11", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-16", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-14", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-3", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-14", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-4", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-14", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-1", 1 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-16", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-20", 1 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-17", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-20", 2 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-18", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-20", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-19", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-24", 0 ],
													"disabled" : 0,
													"hidden" : 1,
													"source" : [ "obj-2", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-6", 0 ],
													"disabled" : 0,
													"hidden" : 1,
													"source" : [ "obj-2", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-24", 1 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-20", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-26", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"midpoints" : [ 47.5, 689.25, 239.5, 689.25 ],
													"source" : [ "obj-21", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-45", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"midpoints" : [ 47.5, 690.75, 426.75, 690.75 ],
													"source" : [ "obj-21", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-9", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"midpoints" : [ 47.5, 691.25, 90.25, 691.25 ],
													"source" : [ "obj-21", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-17", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-22", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-18", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-22", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-19", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-22", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-30", 1 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-26", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-26", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-28", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-26", 1 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-29", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-1", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-3", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-11", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-33", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-28", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-33", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-29", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-33", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-43", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-33", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-44", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-33", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-37", 0 ],
													"disabled" : 0,
													"hidden" : 1,
													"source" : [ "obj-36", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-1", 2 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-4", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-83", 2 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-40", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-45", 1 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-43", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-45", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-44", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-42", 1 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-45", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-26", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"midpoints" : [ 30.0, 700.5, 239.5, 700.5 ],
													"source" : [ "obj-47", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-45", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"midpoints" : [ 30.0, 701.5, 426.75, 701.5 ],
													"source" : [ "obj-47", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-9", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"midpoints" : [ 30.0, 701.5, 90.25, 701.5 ],
													"source" : [ "obj-47", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-46", 1 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-48", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-1", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"midpoints" : [ 70.5, 239.25, 137.0, 239.25 ],
													"source" : [ "obj-5", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-48", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"midpoints" : [ 179.5, 1837.0, 302.75, 1837.0 ],
													"source" : [ "obj-50", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-51", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-50", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-49", 1 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-51", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-46", 0 ],
													"disabled" : 0,
													"hidden" : 1,
													"source" : [ "obj-53", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-49", 0 ],
													"disabled" : 0,
													"hidden" : 1,
													"source" : [ "obj-53", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-13", 0 ],
													"disabled" : 0,
													"hidden" : 1,
													"source" : [ "obj-54", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-30", 0 ],
													"disabled" : 0,
													"hidden" : 1,
													"source" : [ "obj-54", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-42", 0 ],
													"disabled" : 0,
													"hidden" : 1,
													"source" : [ "obj-54", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-80", 0 ],
													"disabled" : 0,
													"hidden" : 1,
													"source" : [ "obj-55", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-81", 0 ],
													"disabled" : 0,
													"hidden" : 1,
													"source" : [ "obj-55", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-82", 0 ],
													"disabled" : 0,
													"hidden" : 1,
													"source" : [ "obj-55", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-61", 0 ],
													"disabled" : 0,
													"hidden" : 1,
													"source" : [ "obj-58", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-63", 0 ],
													"disabled" : 0,
													"hidden" : 1,
													"source" : [ "obj-58", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-65", 0 ],
													"disabled" : 0,
													"hidden" : 1,
													"source" : [ "obj-58", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-62", 2 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-59", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-61", 1 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-62", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-74", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-64", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-75", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"midpoints" : [ 30.0, 1000.0, 265.75, 1000.0 ],
													"source" : [ "obj-64", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-83", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"midpoints" : [ 30.0, 1002.0, 511.75, 1002.0 ],
													"source" : [ "obj-64", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-62", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-66", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-67", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-66", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-68", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-66", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-63", 1 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-67", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-65", 1 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-68", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-62", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"midpoints" : [ 30.0, 1422.0, 511.75, 1422.0 ],
													"source" : [ "obj-71", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-67", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"midpoints" : [ 30.0, 1422.0, 265.75, 1422.0 ],
													"source" : [ "obj-71", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-68", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-71", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-80", 1 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-74", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-81", 1 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-75", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-74", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-77", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-75", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-77", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-83", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-77", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-82", 1 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-83", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-13", 1 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-9", 0 ]
												}

											}
 ]
									}
,
									"patching_rect" : [ 32.0, 185.0, 774.0, 377.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 7.0, 92.0, 774.0, 377.0 ],
									"viewvisibility" : 1
								}

							}
, 							{
								"box" : 								{
									"angle" : 270.0,
									"bgcolor" : [ 0.32549, 0.345098, 0.372549, 0.19 ],
									"border" : 1,
									"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"id" : "obj-3",
									"maxclass" : "panel",
									"mode" : 0,
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 9.0, 211.0, 766.0, 379.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 9.0, 94.0, 766.0, 379.0 ],
									"proportion" : 0.39,
									"rounded" : 0,
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"fontface" : 2,
									"fontsize" : 13.0,
									"htabcolor" : [ 0.803922, 0.898039, 0.909804, 1.0 ],
									"id" : "obj-26",
									"maxclass" : "tab",
									"multiline" : 0,
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "int", "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 7.0, 72.0, 354.0, 23.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 7.0, 73.0, 530.0, 22.0 ],
									"rounded" : 4.0,
									"style" : "",
									"tabcolor" : [ 0.25, 0.25, 0.25, 1.0 ],
									"tabs" : [ "Number input", "Number output", "List input", "List output", "Locale" ],
									"textcolor" : [ 0.95, 0.95, 0.95, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontsize" : 13.0,
									"id" : "obj-1",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 7.0, 34.0, 613.0, 50.0 ],
									"presentation" : 1,
									"presentation_linecount" : 2,
									"presentation_rect" : [ 7.0, 34.0, 760.0, 36.0 ],
									"style" : "",
									"text" : "Many sy objects share a small number of attributes, dealing with numeric conversions, list handling and locale. \nHere's the help center for these common attributes."
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-5",
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 667.0, 26.0, 30.0, 30.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"fontface" : 1,
									"fontsize" : 16.0,
									"id" : "obj-2",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 7.0, 8.0, 339.0, 24.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 7.0, 8.0, 339.0, 24.0 ],
									"style" : "",
									"text" : "Common attributes for sy objects"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-26", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-10", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-9", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-7", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-7", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-9", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 390.0, 1180.0, 90.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"globalpatchername" : "",
						"style" : "",
						"tags" : ""
					}
,
					"style" : "",
					"text" : "p commonattrs"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.25, 0.25, 0.25, 1.0 ],
					"fontface" : 2,
					"fontsize" : 13.0,
					"id" : "obj-11",
					"maxclass" : "textbutton",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 553.799805, 1061.0, 191.400391, 21.40625 ],
					"presentation" : 1,
					"presentation_rect" : [ 586.0, 373.0, 189.75, 39.0 ],
					"style" : "",
					"text" : "Some common attributes for multiple sy objects",
					"textoncolor" : [ 1.0, 1.0, 1.0, 1.0 ],
					"truncate" : 0
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"bubbleside" : 3,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-10",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 64.0, 1071.0, 459.0, 40.0 ],
					"presentation" : 1,
					"presentation_linecount" : 2,
					"presentation_rect" : [ 287.0, 373.0, 299.0, 40.0 ],
					"style" : "",
					"text" : "Learn more about attributes handling numeric conversions, list handling and locale here:",
					"textcolor" : [ 0.25, 0.25, 0.25, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-29",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 21.0, 217.0, 49.0, 22.0 ],
					"style" : "",
					"text" : "zl.nth 1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-27",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 21.0, 184.0, 49.0, 22.0 ],
					"style" : "",
					"text" : "dict.iter"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-15",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 4,
					"outlettype" : [ "dictionary", "", "", "" ],
					"patching_rect" : [ 21.0, 153.0, 71.0, 22.0 ],
					"saved_object_attributes" : 					{
						"embed" : 0,
						"parameter_enable" : 0
					}
,
					"style" : "",
					"text" : "dict sy-objs"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-12",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 21.0, 120.0, 184.0, 22.0 ],
					"style" : "",
					"text" : "import sy-obj-qlookup.json, bang"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-18",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 223.0, 752.0, 992.0, 36.0 ],
					"presentation" : 1,
					"presentation_linecount" : 2,
					"presentation_rect" : [ 7.0, 280.0, 571.0, 36.0 ],
					"style" : "",
					"text" : "sy is a library for enhanced symbol handling in Max by Daniele Ghisi, based upon ICU4C.\nPlease send bug reports, requests or feedbacks to danieleghisi@gmail.com.",
					"textcolor" : [ 0.25, 0.25, 0.25, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"align" : 0,
					"bgcolor" : [ 0.74902, 0.74902, 0.74902, 0.0 ],
					"bgoncolor" : [ 0.54902, 0.54902, 0.54902, 0.0 ],
					"fontsize" : 13.0,
					"id" : "obj-1",
					"legacytextcolor" : 1,
					"maxclass" : "textbutton",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 228.0, 634.5, 100.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ -200.0, 245.0, 115.0, 20.0 ],
					"style" : "",
					"text" : "Open help patch",
					"textcolor" : [ 0.663438, 0.0, 0.813251, 1.0 ],
					"textjustification" : 0,
					"textoncolor" : [ 0.15, 0.15, 0.15, 1.0 ],
					"textovercolor" : [ 0.445652, 0.445652, 0.445652, 1.0 ],
					"underline" : 1,
					"usebgoncolor" : 1,
					"usetextovercolor" : 1
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-25",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 187.0, 725.0, 74.0, 22.0 ],
					"style" : "",
					"text" : "prepend set"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-24",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 187.0, 692.0, 80.0, 22.0 ],
					"style" : "",
					"text" : "sy.nth ( 3 -1 )"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-23",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 578.0, 142.0, 81.0, 22.0 ],
					"style" : "",
					"text" : "loadmess set"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 72.049176,
					"id" : "obj-21",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 399.5, 187.25, 323.0, 87.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 188.5, 114.25, 391.5, 87.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"bgmode" : 0,
					"border" : 0,
					"clickthrough" : 0,
					"embed" : 1,
					"enablehscroll" : 0,
					"enablevscroll" : 0,
					"id" : "obj-19",
					"lockeddragscroll" : 0,
					"maxclass" : "bpatcher",
					"numinlets" : 1,
					"numoutlets" : 0,
					"offset" : [ 0.0, 0.0 ],
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 7,
							"minor" : 3,
							"revision" : 0,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"rect" : [ 760.0, 301.0, 401.0, 85.0 ],
						"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 1,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 1,
						"objectsnaponopen" : 1,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"lefttoolbarpinned" : 0,
						"toptoolbarpinned" : 0,
						"righttoolbarpinned" : 0,
						"bottomtoolbarpinned" : 0,
						"toolbars_unpinned_last_save" : 0,
						"tallnewobj" : 0,
						"boxanimatetime" : 200,
						"enablehscroll" : 0,
						"enablevscroll" : 0,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"style" : "",
						"subpatcher_template" : "",
						"boxes" : [ 							{
								"box" : 								{
									"comment" : "",
									"hidden" : 1,
									"id" : "obj-1",
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 103.0, -123.0, 25.0, 25.0 ],
									"style" : ""
								}

							}
, 							{
								"box" : 								{
									"border" : 0,
									"filename" : "helpdetails.js",
									"id" : "obj-11",
									"ignoreclick" : 1,
									"maxclass" : "jsui",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ -1.0, -55.0, 675.0, 157.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 20.0, 147.0, 382.0, 156.0 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-11", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-1", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 150.0, 361.0, 128.0, 128.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 213.0, 201.0, 401.0, 85.0 ],
					"viewvisibility" : 1
				}

			}
, 			{
				"box" : 				{
					"data" : [ 2779, "", "IBkSG0fBZn....PCIgDQRA...fE...vGHX....vXHq.3....DLmPIQEBHf.B7g.YHB..JHYRDEDUnEX6Z0FaSccF94dsAM5Dd9eaSNHLBso3HshCEnkNZi85VmZoo45k.EZnCalVaWYcIoDBai7kABzXBywqeoMsl30tpVsREluV6Bc3aHnEm3jXynEmerJaTRToZSyAGzTI9i28iqum3archCsczw5izQ2iOe7bO2my64q2i4HhzvwwcU7E3yBvwA.B.3z8bJvyyCdddnRkJvyqBp34AupzO44AGGO343.GGW5pB.h.ABTJBonTHUJoPxjIkdlJIRlLERkJIKuTTJV4IhRSCwheq.1TEaF..b.fjEWUpTIE3UMSbUpjxiWUZQlCbb7YpuoEmzBaJIwLYxzgLimToHmJUJlvloPeqB1TEaFpAfRwUkZnVwSovIO9ofWudwfCNHlJ1TJHZoZVJV25VGL+cLixe3GBISoB77Ij5PRxCNvAo9xY.khjFI.HMFhSRbGwe.34s7fPgBon7FLX.BUJfUu1RKnOtOuvCG.n+7YeGnVsZlnpVsZofJ0nWwyAGOqCLwDSTPMHc5zgF9EMfxJ6dQhjIQxjIPhDoCISfDIRxrvyzR9Cm3Cwy04yiQCMJ..LYxDLZzH..BFLHDEEA.PwFJF6rlchu1W+qly2+U9vOBufqW3yE7roJ1rj.+t8dFnVk5YDV0KBKRsZzRSsBOGyCqBZ0pEBBBPud8nrxJC..81auHRjHviGOXxImjUVAKBn9F1EVxssDjHQBDOQBjHQbjHQBkSYPovUidU7SexmFwhECBBBvoSmPud8JZrQhDA0UWcviGOPiFMnMGsk0G00hcMTyNq8yM7HOOLc19NK0W+mi52e+zPA8SW38BRBVDHHM3kzpUK0ZqsRQiFklKzc2cSZ0pkUuhMTLc996iFJ3Pjug5m5q+yQd66rzYD6gdm+xaSmtmSQm3sONYvfAB.jUqVUvmLOy9cHy8ad7+nhPwFJNm73xoS5Qejs7IhmwFaLxW+8S95ueZrwFqf3A.DO.fpzyAqVkJnVkRKWiFMh.ABfVZoEnUq1rFFjIrZ0JBGNLanzngFEc33HJlKmmsiDoci32meDJTHHHHfF18tmS9keGBBBXzPihQ7Gfk9H9CfQCMJVcokh69tVOK8ecmchm0gCbxSeZrm52MFe7wKHdxr87GdkWAl1v8fp2xVQ0aYqvzFtGbld5YN4ISP84qOx2P9nQtvvjqmyEyxwnQiyqUatPznQIiFMx3w0y6hF4uMBMvv9ny6qOx64krhe628OQFJQx5Mb3vEL+gCGl..YvfAl0h7nfh+FeSZkKWOU12dCzS9iebB.Tqs1JcnCdHB.zQey2rf3Qt83q+9k36NWO8i1tMpgcUOsxkqmV4x0Stb5Lu7jCKXIqXGOqC.HMea2c287Z0lKnUqV30qWVccbHGo2KcZKXtz6olmGgtTHXxjorliylMaLqba1roHO850CSlLoXk8Pgj3o7xKGaZyaFiO933L8zCV4x0i+8TWCa6w1Ftz6+9nxpppf3Qud8HVrXHTfKB.fJD9A324tKzdGGF6s4l..f6t5Nu7HCd.jdXqzVwj2sPs0VKan9MBzpUKb5zI..lXhIvIOwoXGXQRj4XaSKWuG2tcmy3xHW0wnQivwQ5.GxQ630diWGUVUU3CtbD33HcfksrkA2c0MBcoKUP7Hi19URFb+1e+KyR66c+2O..hEKF9nqbk7xCPZAV1ZxqWu.PRbpolZXERTTDVrXAlMaFlMaF1saOu40YmcxxypUqLqXum0aFVubfieFA9yBbm20cg163vXrwFCMrq5QoeqaGu0QOJJ+A2HpdKakMG5bAMZz.WtbgaSyRwK8RuTNKyG+wWeN4P5fFbbfmiCCN3f..PPPfILhhhvrYyJpjnnHDEEQM0TCrXwRV4cgKbAzc2cy3xsa2XvAGT5DfoEVIwURfCFLXVMLqVsxrbsZ0ZV4mq5L6zhEKFNSO8f163vv5krgxevMB.fA74CC3yGJpnh.2hTOm7rH0pQC0WOtskrDVZC3yGK9x0u771d.XVvRevxmPaUqZUrBTWc0A.o4YBGNL750KzqWO1912NyR1nQiHb3v3XG6XJ1iL.XwmJ1TRuGvkwSfRJoDHJJhHQhnngI2AM63.R6AUTTDFLXfklACFxhmexi+Dns8ser5aeUn5srU7AWNBprppP6cbXT811VAwy3iONZs4Vvi9HaAssu8i1129QyM1H..18d1SdaOJDXvAECWyb9D4dFqVsxlLOb3vvpUqr7jO7gff.KOYj4hWRFsJO17ldDoEcj6HKDHWVgJEXoIGOSdZuiCCa6XG3J+y+A96gCCWNch81bSnxppB1Ov9QoqcMyKO11wNfscrC..zcWcgt6pKb8O95Xik+PXqU+n4s8HirGe7eYr9MrdXnDCviGOvlMaYYsNaHe5ohMTrB+.r50VJJ1PwJ3onhJB6s4lvWZIKAiL7v3mUas2P7r2laBe+G3AvkubD.HMpyPIkLm7HCIKXRoWrxb9DYqY2tciImbRDLXPrhUrBX2tcVdxGSNy7jQlCYkNal71imAM0ZSPiFMvsa2vhEKr5PY3ksHQh.KVrfN6rSnQiFryZ1YVeL64W1PN4YW6td7Zuwq+Ihm0r10fJqpJTYUUACkTRAwCPZm83ejAwhW7hwFt66ASEaJX0pUlkjGOdxZgL.ooLpnhJxadx0ut5pCc1YmXoZVJN+esOL8zSioiOMhmHNhGOgjyfRl.Q+WShCZ+fr8RZznQXznQnUqVHJJx5zmOmzbsXWCsePGLmzbyjGlydFX3AvhW7hg8lsCOGyCzpUKhFMJqfhhhvkKWLm4XxjIzRKsv5.b4xEqrYlG.vJVwJPjHQv88cuObDmcfqO8zH9rDXY+FmJYJ3e.+3XG8luaF+zfGl.6an9whVzhw4O24QMOsz9ec5zIpMi4rtQfa2tYmB6.G7.3A23CfoiOMlNdbjHdbDOwrD3b3.9+WFaphMKMGr7U5XxbYPmNc..vtc6Ys0oEBlbxIYqtpSmtzNhO8sXjJERkdtXJ8UNcqJ3A.RQoPxjR2i19aae.PRfrXwhBe7VnXxImDlMalU2F94Mj1A6ImQjy3JiXKxNqEauUAD.nFaoQx+HCRAuX.5w9gOlBOpEHPfEjmtxzSZBVDnfWL.4ejAo8019Xo++QgY9QsOSMzPA7SAuAb3dznQoVasUENbesqaszEdufzPA8SM1Ri2r+PuoDXWauLZpkFQEVDfZ0pwQbbD7puxqxxagdkQ12eqHQhDXfAFDO0S7TX9PlSOHexRhHEmxb1+Ne7ju5H+NJTGMku1zBhiYGZpkFkrjuX.pK2uLoSmtBtGSmNcjqmyEE7hAngB5mdweyKVv0kHZNimYZyGOyW8KDtxUYVnbjkErLp8YpAUuspYW0in2dwIN9Ilyqs+gEdXXxTYrKz73G+D3.1OPAzGKgbYsjYdKDqNNNt79bgfYasN6EgmO9xq.C.r56nTzTKMihVltLtMhLc2HTruU4+3ISL933W0gSbtdO2B9i4SxTC4iG.jk.uPE6b0IUHbLmBrLt2xtWrwx2Hti0bG3qnQS5+5TxuYoWzUiECCOzv3zm7zKXgMyOBVC6SAK3b86Ex7my2ZBepIveAtwAOQzW9lci3VXv8efsp5.NAVz1iC....PRE4DQtJDXBB" ],
					"embed" : 1,
					"id" : "obj-92",
					"maxclass" : "fpic",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "jit_matrix" ],
					"patching_rect" : [ 223.0, 803.0, 88.0, 32.0 ],
					"pic" : "Macintosh_HD:/Users/danieleghisi/Documents/Libraries/Max/bach/prove_in_vista_della_0.2/bach_objects/license/cc88x31.png",
					"presentation" : 1,
					"presentation_rect" : [ 10.0, 328.0, 88.0, 32.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-9",
					"linecount" : 2,
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 223.0, 893.0, 453.0, 35.0 ],
					"style" : "",
					"text" : ";\rmax launchbrowser http://creativecommons.org/licenses/by-nc-sa/3.0/"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-115",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 315.0, 801.0, 478.0, 36.0 ],
					"presentation" : 1,
					"presentation_linecount" : 2,
					"presentation_rect" : [ 100.0, 326.0, 478.0, 36.0 ],
					"style" : "",
					"text" : "sy is currently licensed under the\nCreative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License",
					"textcolor" : [ 0.25, 0.25, 0.25, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-3",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 6.0, 32.0, 145.0, 22.0 ],
					"style" : "",
					"text" : "loadmess bang @defer 1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-89",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 405.0, 501.5, 60.0, 22.0 ],
					"style" : "",
					"text" : "loadbang"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-88",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 405.0, 524.5, 206.0, 22.0 ],
					"style" : "",
					"text" : "presentation_rect -200. 245. 115. 20."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-85",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 470.0, 569.0, 202.0, 22.0 ],
					"style" : "",
					"text" : "presentation_rect 213. 105. 115. 20."
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-70",
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 63.0, 738.0, 20.0, 20.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-68",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 64.0, 796.0, 81.0, 22.0 ],
					"style" : "",
					"text" : "prepend help"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-67",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 64.0, 825.0, 53.0, 22.0 ],
					"style" : "",
					"text" : "pcontrol"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-66",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 64.0, 768.0, 40.0, 22.0 ],
					"style" : "",
					"text" : "zl reg"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-42",
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 6.0, 64.0, 20.0, 20.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-35",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 6.0, 333.0, 81.0, 22.0 ],
					"style" : "",
					"text" : "prepend tabs"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-32",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "bang" ],
					"patching_rect" : [ 6.0, 85.0, 34.0, 22.0 ],
					"style" : "",
					"text" : "t b b"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-28",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 6.0, 301.0, 100.0, 22.0 ],
					"style" : "",
					"text" : "zl 512 group 512"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 1,
					"fontsize" : 13.0,
					"htabcolor" : [ 0.9, 0.9, 0.9, 1.0 ],
					"id" : "obj-26",
					"maxclass" : "tab",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "int", "", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 6.0, 361.0, 134.0, 345.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 584.0, 4.0, 194.0, 353.0 ],
					"rounded" : 4.0,
					"style" : "",
					"tabcolor" : [ 0.25, 0.25, 0.25, 1.0 ],
					"tabs" : [ "sy.append", "sy.case", "sy.collect", "sy.compare", "sy.convert", "sy.empty", "sy.filter", "sy.filterempty", "sy.find", "sy.insert", "sy.is", "sy.iter", "sy.itou", "sy.join", "sy.length", "sy.normalize", "sy.nth", "sy.pad", "sy.perm", "sy.prepend", "sy.replace", "sy.rev", "sy.rot", "sy.route", "sy.scramble", "sy.slice", "sy.sort", "sy.split", "sy.subs", "sy.transform", "sy.utoi" ],
					"textcolor" : [ 0.95, 0.95, 0.95, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-8",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 662.0, 287.0, 60.0, 22.0 ],
					"style" : "",
					"text" : "loadbang"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-112",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 662.0, 318.0, 46.0, 22.0 ],
					"style" : "",
					"text" : "jsargs"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-79",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 449.0, 318.0, 76.0, 22.0 ],
					"style" : "",
					"text" : "jsargs $1 62"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-7",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 385.0, 267.0, 150.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 89.0, 243.0, 34.0, 20.0 ],
					"style" : "",
					"text" : "0.2α",
					"textcolor" : [ 0.25, 0.25, 0.25, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"hidden" : 1,
					"id" : "obj-13",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 702.0, -2.0, 56.0, 22.0 ],
					"style" : "",
					"text" : "onecopy"
				}

			}
, 			{
				"box" : 				{
					"data" : [ 22313, "png", "IBkSG0fBZn....PCIgDQRA..AvB..D.KHX....Pd84Xc....DLmPIQEBHf.B7g.YHB..f.PRDEDU3wI6cdGeTUk9G94LS58dHPHTCPn2B8NAH.AAKfEDTA6MPcc000cQ2UWa6thx9yBJhHhhzDjhHnzkdQP5cPBPn2RcxLme+wcFHDRlDx8NIyDNO9Ie1M24deOmIj4aNm2yaATnPgBEJTnPgBEJTnPgBEJTnPgBEJTnPgBEJTnPgBEJTnPgBEJTnPgBEJTnPgBEJTnPgBEJTnPgBEJTnPgBEJTnPgBEJTnPgBEJTnPgBEJTbqBMoIMomMoIMYYMoIMYFiXDinFUzyGEJTTIEoT58XFyXLoCSbm.4C79.2aTQE0e+bm6bgZLyNEJTnn.7O9G+iGDH0xxylbxIWO.K.ixw0BKrvpwW7EeQOLlYWkWzyegPghaYYG6XGc.XzkkmUJkuMv5.9.GW6BW3BGQJk4IkReMnonBEJTnwTm5T6NfUfZdy9r0qd06..2VgutTJMIkRcsHB897JTnnRHRoTT6ZW6cA7V2rOaxIm76A7XF+rBLYxzia1r4o.TozI9J0XEJJCHDBYUpRU9HfG.vmB9Z6YO6o1SZRSJswO9w+3SbhS7Ql3DmXGK3qa1r4+NPh.uJfeE2Xr3Eu3lb228c2A.5Se5yimZpo1hwLlwXZHCYHiIiLxHnh5YrYy1LrZ05tAlqc66uddepPghJIzpV0pn.xL7vC+5b99sca21rAj96u+GAHc.YhIl3RN1wNVjExDOBv2Az8hx9ewW7EOFvGC3Mv9A9L.7yO+VaFYjQUJloUOPyY90DXx.KC31uoey4lhZEVJTTFYSaZSmAXglLYZDE754jSNA1yd1y4lc1YWCz1ZVG2291WmG6XG6SWHS7Y.+MfgU6ZW62Z+6e+wTvWLxHi7b.4BzAfOGvWfDyO+7Oy4O+4KtUNUSf1BbXfgAbHfIBLmHiLxVW1e25dfRvRgB8wWXwhktbhSbh.cbAgPH8yO+rX+ayGX0.KcCaXCsoHd98BLhCdvClScqac+i+7e9O+7NdAKVrjIZa2ra.yAsUKcO4me9WNqrxxe.1912tO.C.sUgAPi.xv9++ZAzUf1ALqye9y+ICYHC4+sycty3Lh23UDnDrTnPerrKe4Ke5LxHiqa0Q1rYSTn6KmbxIGyEmQ5e+6+GNrgMrON1Xi8HRoT.fe942UPSzINzD1lCPqAh1jIS9Z2ndAb2.q.n+.KE3qsa1+KvzA1MvjBHf.56ku7ks06d26ueMqYM0TWuqUnPg6O6cu6M9su8sW2BdsHhHhW4BW3Bg6366Uu50hSKszlVgdzY21111EdyLVG8nGswnsBs+dAt76BHW8pWcgWsV+PakbSFn5.cAXe.NbNeyMa175G6XG6cdjibjpJkRORmwqVgkBEkNhVHDeQCZPCNXSaZS2mISlVAPUAHf.B38CKrvNeAtW4wN1wpwy8bOWpnEM7oBDe94murfFbcqacQ5X0TEEexm7ImOxHibiIjPByyw0hO93Gecqac+eRoLiBc6K.ny.aD3aAlIvaCbEf+JvT82e+mPngF57qQMpwwEBQ1NdvktzkF0O+y+bKm1zlVwtBPEJT3gv3G+3iGXq.Rf8.7d.SCXM.2P9+MhQLhOOxHi7zgEVXWL1Xi8hwFarWLlXh4z8qe8a7Evl2aLwDyLbQS4QilerVAviBLDfBeBkNP.7En8d6obQyGEJTTdvd26dCIwDSbSn8A5OAHfB7xOBv+pvOiTJC3bm6bgV3ujR4Ue1G6wdr20Ku7Ze1+1n.ZNfWFvTNLfC.jLPiAlGv7A5jSdlZBbAfCLsoMMebx8oPgB2Y5YO64jQSrZREys75gGd3M9l0t+zO8SscnCcnOSbwE28Abd6iw5.huLOY03CA9lBcs6BXCnEdCAdCOgFuNfbRSZRsPmiuBEJpHXxSdx8FMgjcQw+A8FDYjQ9RE0Kjd5oGvxW9xa4BVvBJxDZddyads0rYyYh111FHvIA1IPDkwobxnsUvpUDul+.2KEejuWW.43F23dnx3XqPghJRZUqZ0B.jMsoM8Nb18EQDQbGRo751JkTJ8uMsoMe.Z9QZcSZRSJxB7Zlm9zmda6cu68r.9KE3wpGZq1ZUTLBKolZp9NfALf2KszRadokVZ+8zRKsqtMy3iO9tBL7Bb62rGp1tG8nG8+7l7YTnPQEMG8nG0ee802Lpd0q9eLlwLlaZ+5rqcsqlDczQ+Dnkqf+y9zm97sNdsctycFo2d68wPqZOz0B8nICjGZwbUQI37onE9B8F3+U8pW8YIkxhx2WMlqsMvpWJm1e1y8bO2GVJuWEJT3tfTJ8NnfB5DokVZ+XY44OwINQfIkTRSAM+RYxau89+7Mey2b0RJyLlwL5BPN.Ek86EZaEcBE7hsoMsoV.m.6gSgc15JW4JaUQXi6E331syYA9STxIB8C+7O+y+9kv8nPgB2QdrG6wdyFzfFr6x5y+Ue0WEHPy.LMlwLlfF9vG9ab5Se5fc75iabi617xKuj.+uh3wuG.4ccW20a63BsoMs4U.Vdgtuc8i+3O19hYJ75nIvYEMgqsALHmLk67nF0n9KN40UnPQEECdvCtICX.CH1h6026d2qusoMsYgIjPBkXMuZiabiATR2yJVwJZ5Tm5TStfWKhHh3AQSL4uWDOxSCH+vO7CuW.pScpyVQyo7N3thIlXNb5omdgG6ZgVfj9Y.UAnU.Kz93HA9Afh5z.q1+8+9e6bI89PgBEkiHkRSolZp2EPS.JXzceCQ58QO5Q8ussssyBsDOd.nI.TPpNvxZTiZzJjR4UedoT56ce228eBsfLsOu268dAZ+5EUzj+hnIj77E9ERIkTtu8t28F+ZW6ZaFZmV4G.LKfwBbrN1wNV3CDHMfMiVvhVXtazxqPIZaGcrTFpXpJTnnbjLxHifhKt39Qt9.0LYt9SXqv7Qn8A8z45it8nANQm6bmmoiU5bnCcH+Ze6a+LqYMq42fVTjumPCMz8s3Eu3lTbFO93i+sqZUq5MHX4fAO3A+4n4.c.5IZQydSK36oa61ts2w9b7vnUWrJJBBsUX4X0V2aw+VVgBEtELjgLjW.sn.uIncRduEZqfpXwrYy2lISlViISlttOjGRHgbcwM0K+xu7S+hu3K9ZSbhSzOzDzHgDRXLO3C9fEkuptANyYNSHomd5Qs+8u+XbHBNkoLk97.OvCzfh6Y15V2Z7st0sdhn4yJGhQiEsTuovrJ6u9KVZlOJTnv8fAiVTg+LnUr61Nv3Adh5V259jG5PGpHKewqZUqJ3h55fVsduO8oOezTlxT5Z0qd0mKZ9b5e1st0s19JuxqTpDHF23FW6iN5nuPzQG8wlvDlPsuIeOEAZkF4rQST5sKzq2N6W+q4FwuwMtwUb4bnBEJbSvwpPZHZ0Spw.7AolZpeQw8.wGe79W6ZW62rd0qd0pPuj296u++yfBJnm.sThIFfqjTRI8sG3.GnXcveQvT.dCGey92+9io5Uu5KIt3hqzdJdcDsndWx06f8uGsUgEVQ7L2d0pV0195W+5KswskBEJpfIXzRx4MM3AO3wVL2iebM+.8BEwq+J.029q8L.q3EewW7UuYlDSaZSybAK2KRoTT+5W+s.jIEeZBECv54ZBccx9b7is+8Mz92mVw77eOfLnfB5vqXEqng2LyWEJTTAxHG4HuuibjiDdQ7RETr5inPcLG6zU.GwFUP.8YTiZT2ff0RW5R8ZiabiwszktzaHR0SO8zipv0JqjSN4mw93V3ni2Aiw9q2qBbswgVIwAzDjldw7rcCPZ1r4bZQKZwhl5TmZGKl6SgBEdHTXwJmQA8yUW9e+u+2PKzq+r.aAsvLXWspUs5tJ3K15V25oOwINw9Wvq0pV0p5fVPfNdzVMUASp5fAtHZwaUAolnkOicCssBVTcamjPqP+8Ku4a9l2zUdBEJT39QoQrp3Zy7o8oe5m1AGeSqacqGEvoQq8dENvCXxjobKXDq+lu4a9XcoKcYpEgs9U6ygyiV0cXW.KA3Wre8hpQW7OA9MfmrHdspilutlNE8pEUnPgmD1COgRRrZ.ncJiEkfwH97O+yqJ.RozqZTiZ7G.Or8Wqt.2Gf0TRIkqJPczidzHhLxH+sB25u3ZAY5ifV567mQqEfIQaKeEEeLvl3FCwgX.NH162gJTnvCmidzi5eW6ZWmCNWrJUz5efYh1oyUPB.3EFyXFiIG1KhHhHczNMx0B76.+P8qe8erEsnEkTA8aUu5Uu9p+1e6uU3UEkDWSvxAOr8qUTIAcXnEZEEthiFNZBrE2AKnPgBOIjRoussss8GQSL3mJlaKUzJGLWfq4n8qx.G3.CqO8oOWW94kTRIsQzpQ7MG6kb4vBKrl14N244WvVP+29seauqQMpwpJT4iQf11.cjDzAgV0XX1E0jaTiZTgMpQMpaqPWNTzDKKX4c1DPipScpyesCcnCeSG6XGeysu8sGDJTnvy.oT508bO2yailf0E3FyOu9x0DqZWwXiavuVsqcs6wQaEYN19Xr.aqacqaKnPOqO8rm8b76cu6M5BYhWy935CZgMgjBjlNNiniN5fPymWE9TKGMZ945+flH7a18t28utXx8QEJT3tx8bO2iivEHezRfXnDVYE.sqcsqtIjPBaaLiYLEtE0aBsvM3Bn4aocEQDQLs8t28FRobJ0L6ym6BsFNwLKMOz1291Cxe+8+m.JpR5bznI.ZFsscRzQG8D9we7G6VobNoPgB2HbHZYAslYZlncRcE4JqPyY5G.PNlwLlQWT2vjlzjp2jlzjR4K+xurNfVMf+1u8ae7cqacalezG8QCtXVcSXnI3sSzbXdtnEPnNkCcnCEVhIl3OQQTQHJ.CCssp9q94meuTjQF43+5u9qGXIYaEJT3dhCQKGaQr4Ey8UWfCXxjI4a7FuQgWcUwxq7Juxnaaaa675QO5wj.jCaXC6Mc7Zm9zmN3DRHgGFnk1uzKgV9B94kjckRo4jSN4IOhQLh+TIbqIATCz7q1dpScpyZJhZskBEJ7fvgn0konqdmWckUCdvCtXEqjR4MTu1m8rmcq+xu7KaSspUs1bMqYM2xm8YeV+.sp2vPG5PespTkpTvURYBstiiixdbwJrHkRw1111JUIQcG5PG5MZaS8yW5RWZTklmQgBEt2TT9zBJfXEZUKT.3Mey27IZQKZw1aVyZ1NZVyZ1NZTiZzNlwLlQ2KrQyHiLBJv.C7XokVZecAWYyfFzfd+O+y+79W36u.7Z.ubocxOxQNxXG4HG4eaDiXDS4ge3G9wcDxE.7QezG04ANvA1sRqsTnPgmAETz51QaqT2fXE.KZQKpmnU785APOG6XGaOKXsc2Ae0W8U8p5Uu5+ZAul8J7vo2wN1QMbxb4fn4.9RKMAs569DA9s5Uu5M+B2lxTnPQkObHZkMWqv4cCaC7S+zOcvQEUTkXsRO8zSOpjRJoouoMsojbbsyblyDhO93yEsmlNEUa+JHzZE8NhUqdBD9y7LOSCKkgjf2.+9y8bOWQ1LXUnPQkKJni3uAwJoTJZTiZzh8wGeNIv9AduktzkVjEFP.9ke4WZTyZVy9g4O+42ZGWaricr2oc6udz5GgELPRGAZID8OhVBU+1.gT8pW8ETX+jM5QO5+FZaerv7WZdya9ZKMuYUnPgGN96u+uQ.ADPQdBbRozq+2+6+cWcu6c+9.9q.Gpcsqcy19qI12912UKVdG9vGNNoTJ9se62pW6ae6+vCcnCc0hr2Lm4LaWjQFoiRa7wPqpLLOz51N2FZNJ2BvN.tym8Ye1Guvykt28tuNzZDqElklRJoL2x16dEJTTYlfLYxzpmyblSOjRoH5ni9a71auaTW6ZW8pMsoMSygH0V1xVBqvARZ6ZW67GsvZ3oQakc8sP1NQzp7BGYZSaZ2PSS8odpm5cAVYgt7qZxjI4rl0rJtZrkBEJtUlQO5Q2iW9ke4w.PXgE1SgV50z1gMrg8AE2ybfCbfPCIjP9czVY0ilPBIT3RyrCR.nQ.lqScpySU25V2qFKWQDQDgf11J+YzhiqEBH6e+6+nLh2WJTnvCiO8S+Tum4LmYKm9zmdmmwLlQQF6SKXAKHjm8Ye1WAfvBKrZ.LAgP7uW9xWduclsSHgDRAspqvN7yO+tbspUsNva7FuQAiz9DQqP90JzJxeOFZMahqVARqe8qevMrgM7caXCa3VaXCa3OkTRI0S879UgBEdtzdf8x0bBuDXc.8of2jTJEuy67NOdANEuoBrsTSM0aHQoG1vFVBOzC8PiajibjWW2uY0qd008sdq25Q+3O9iqo8K0Vzp6UwfVkavQbdUOf4f1oApPgBEPLwDSrnUlW9EzhKq9B72P6jAknUj9tJu0a8VOpiJ4vHG4H6UZok1CyMRsKvyOtBWi2K.cBMgQG1X3.eXAd8WG3IJCusTnPQkQhHhHFMZqtpvhJ9B7cnk6gW0I5KYIKoiRozamHBAvPQSr58cbAoT5+vG9ve+W60dsGCfku7kGGvn.hx937tnEDoikqsJqv.lUbwEmJUaTnPADYjQ9gns0thhpiVon4FJex+1u8a0qwMtwq+9u+6uvcc5ZCrXJT2YdqacqwOvANvO.Hy4O+42W6BdAfl+p1n8mo4nUEI9tB7n+eQGczeZIHP51yMzdgTnPwMORobo.+WzVMyEJzKa09W4T3myWe8Musu8s27Ce3C+7n0Ac1GZae79AdOfE43d23F2n2uy67N+4rxJqnd7G+w+xvCO7rDBgDHNzhMqWCXRnELo+FZckmWEsDj9jnUNb7FMwSEJTbqH6YO6oZ94meGhqEM5ckq0AcBB3aAVEZEGuqizSO8.BN3fO1i+3O9C3iO9LYf4B7ATDcfm4Mu4E9K7BufyRglA.7N.uk8uOPzpuUENds7XQsBKEJzI4latYYxjoOEsFPQmAVFvo.NJZk+Xe.RAsUYccTspUsrZe6a+5lyblyfsXwxt.NNZBeOLZAAZl.cAnJAFXfOWfAF34NzgNTX0pV0pvqhCzpVDKx9b3t.lAvcfVdNpPgBE2.giVBH+1.a.HKtVeDbw.+o4N24VsB9.G5PGxuYNyYVv14Ur.8C3QQqc2mMvjjRooe8W+0FWD03c.vGe7o+95qu0LnfBJZe8022khNYoUnPghhkvPKgk+2ns8LKyd1yts2LFXsqcsgLsoMMUyffa7HXUnPgAvS9jOYmV+5WeqEBQNlLYJWa1rYCHDSlLU6t10tldngFZtE79MYxDADPQWzPkRoE.SYmc1l0Ly0+bd68MFSnRoTJDBA.BgPje946chIl3dt8a+1WfPHrcCOfGBJeXoPgKfPCMzz16d26KIDBa10M.vlTJsr4MuYusZ0Z4510rYylo90u9Mia+1u8EBnDrTnPw03JW4JVuzktDb89QxDUfelyjIS1PyeZdrnbJmBEt.La1rawpXJvp6balS5AkfkBEUhQJu1BpJr+u7DQIXoPgKfhpMdUQiMa173OoQkOrTnv0fUgPjicmtWg62HqVs5kISlrTQOOzKpvZPgBW.qcsqsVG9vGNV+7yu7qnmK.XwhEyQGczmqqcsq62cP.srhZEVJT3BnpUspWbW6ZWMylMaBgPXyrYyUXhDBgPjYlY5angFpPHD6qhZdnPgB2T17l2bzCZPCZhb8UezJru7wGex7e+u+2ivU+9VgBEdnr8su8fF5PG53nBVrJ7vCOiN1wNdcU7TEJTn3FX0qd09aua3TgHVEYjQdxTSM06o738pBEJpDvpW8p8+9u+6+CwtHhPHj1c7sRrRgBEteTduRqvCO7Szyd2y6t758mBEJpjQ40JsBJtvNzcbu2wfJOeuUdgJNrJkL3AOXe7wGehAHNqVsFmISlphTJiFHLoTFrISl7WJkELLQrHDhbkRYl.WRHDWTJkmB3LBgHCa1rcJqVsdloO8oqpu12BwpW8p8eRieR+ee1W9YOjMrgPHttzmQujPTIj0nayyN6A1ja6G80WeMaCaZQbuUvW+7Ce7qPkhFqfvpzGyMxuCDz.C5Wb2iQKkfUQiYzJ2rMGstnaS.pCZE6+fLnw3Rbsxn6tA1l8u1Cv4LnwPgaHYcrrp93dsw8su5m+W6nEx+pInrdEtpevIxnu7qZqwzVoUrZ1ZgphL1vFRjE5ZZeeq9qw+zQ+lQ++oqIP4.JAqqQL.cPHnOn0XJqOULcK2SCrMojUBrDfMgVY10cCAZ0K7fMH6YAsZPdtkzMVYfI+ASN9irgC80+qo9VcMaqZMSG8HXEq+wv+H62kFSaIWrfDYI9gaIRLiIadg4+RGWZC+uhtKbKhJemws5BVgAzagf6BslNo6Xil7P.+rTxrPq4FbCsJpJJDB9Ff60nrmTRZ.y2nrm6NO3fevlrfed9a5Tm+zdKzwmDk.iT937n7hjMYd0UMUROiWHx2W79uzNR5eW1G8xWtUUvpYBAOHZcVj3qfmK2LrGfuSJ4qQq+0UQSaDBVKF2uGMcojgXP1xSfGDASTO+vSBDhLP9BlCwR0vRonkC5oJVA25UdYZiPv2IDrAfQimkXEnsM0+tPvuID7U.stBd9rAz5CeFEoBTUCzdt0HD7vFgRe6nqDO05lRrxeOPwJ3VGAqDDBlfPvpAFBUL9lxHI.fgIDrVgfICjTEz7PJk7EFn8BFM+hcq.NZm7kYbrwuTYPTZJS6NDq7Cue413AJVA2ZHX8.BAqGs12sGeALqPXF39s+9aL.9UALGlEF3oZJDLLtEvUE1eep6eerNx5PyoMjaI3ZSIfY6hUskj9O5cbqnnxrfUvBASTH3KQqwTVYlfDBdMgfUfVXXTdxY.loAZujAZgAZO2QBDLFe00KF.ASHT3PXnf3PrJD70iVrBp7JXUGgfk.7fUzSjxYRVHXYTN+9191BMp.NTXVHd.CxVtqjJ5z+oRf.k9Q2HUxoDhDDSPdAf2+kVR88nEqfJmEvulID7C.ITQOQpfHHgfIJkTcf+Y4zXtNfMh1pizERfvkQ7nuNeXOBD+wF1vLdk2+hW5N2C64v509tCHD7PFgcRlNQMoNjEYWr2iDvWL8idp9rpvTYaEVMUHXgbqqX0UQH3eHD7FkSCmTJYhFggD.mUbV+xlLabSI4FWeZbiaNI2x9xcUYopCTafdZDFpOLHz9IVwu3VIPvOqE29HXuzRkIAqZHDLWfpTQOQbi3uhV3aTdvL.NuQXHIv7Y5jG4PtjKWhKRGoa2GUNNzj6Ecd3HRfZHSfVSGJQmsCxcmWirsL8LdtSTYQvJ.gfoS4zJqza5zWdhPv+AHkxgg5z.euQYrMvuxevgva7FKXgpSsZRWIk1aT1uBBuEBFpQXndPZDFggUr5z6SBeUqerV6w2sbbPkBeXID79X.9Oo3nnDYBT5KASnD.ARfDL9g+3M9f4BrHf7Iexib4xbItBWhKx4ISQN2f8bwmguIgfIHkzRfy5JGHojIHDn65Ft.3JhrXkxeggxigEz97V+XfCe47yqRu1uBjtfNiYNIfuRenmzWxqDBTTIxr8B42pmwyciJCBVCB3QMZiVPQkHkQPcndjHMhZQhTUhmHHJBlfwWB.uwa7ByHvDhBH+HQhUrgExibIGtHmmSIyfix9YmrM1IaiCKNzUGKWnvUB9iOua1j2HccCA.rVzRVaCIzJ9YlG2ICGSHHWxlVR6GTMnF+4ivQtfQX+xarmNX5lVS6nNTextjSqzep6zhCaDio6Bd5BVgID7AFoAcHdDtLb5DciNQJz.ZBQQL3E9.XCqXEqXCIVQhDI1vB1JPjvHADWc+1lvDAPfDDASMn1zV5DfjKykXexcyJYwrTVHmPbB.iW3RB3MdOh6mGO+4wzetSvIbUU+AaRIeoPXLBV6RrS1obqzLZM4P1DFQDcWIkz9JlvWaD1ublX.FfQXn9xfvDlojbvfMXBFw34NgGsOrDB9yXf9sR6H0CmGU9r7ELKdU92zU5MgSjXg7HStLYRljC4fExi7sKbYCo8LjufdoRd0qaytHmErP1jMYxUHSxDuwaZFslmi+FSfumQKeEhSFmg6qKAvkDYxgY+O5Gy2tn5Rcck4P4z.z8JfzN6KIKg4iY6+cUKXgtPpCWu1tBh6DHT8X.IPUkUkVSmIGmDJC.XC4A7hP+Y8Ldti3IKXEOvSaDFxg.Q2jovmwz4Q44HJhkL4JjEYQ9jeopjcbyhUrQNjMWlKSPDLCkGgwyL3Nk2yUmWFIKVr.NKmoieDe6O2PZXcMXy6fSALaixXqjelywowK7h7HWZ.MtqMklVOix9kSHDBLjfgsGjJQRjkny1EHmR2oVtMkhHiBOVAKgfmBCn3w4PTXjxmh+E+eDGwyk3RW0QukWjO4yk4RDFgyKy+hWS9dDjLPiK7ws++9s74DKUs9uEe7BRjDqlAY9qCiJgnE.mTjAqmUhO3G1Ph23qO8gA5oESVsDcdnPR.ejdQJLfRgy1skmUjdhaatDwSUvJX.cu0.GhAOq7k4w4OgErPtUvE7RKXgL4JjF2EuGimHkQXnqzZMrb1E+NwSMS7ew+2zim382.MuCVMvuYTF6mYdHwJff7HGZOc6dwCphaHDLbLfOq0LZE0iFVJJiLheo2zR2g5klgimpfUevfpaROf7QY37XjIWoDWlsyvDB7BuvO7E+I.Bjfs+UPkhuBl.H.7EewK6gEwk3RzZ5.uAiiPLnUZI.xTjMqhkP9XkZRca+SyK6JRYCqFUjuCvFYsbXN.9ZOlrpF0rA8h91Yix9tXBFsBEotoub6XFuJQ2SHQXjk7G2J7HOkPgP+0LIIPqjslGlQSlj40cFekxYAdiW3C9B.YSlYcZx3XmkybjKvoNR5jd5Wgqjwo33W.rdYaXJGA1rHwrMyHERj9ZCBJDBNrnnpUsJDaMqF0ntQRr0MBhLdevGrPtzF5DOOuFuFundeKeUVIKh6lGDqXkTn+O4.YEyeNLsEXXCfFSCsbYLD8XDAP1hbXExEyH3oIWxCI1HUFzvWL+3RLjYpqk9gN+iqRfXjwP6nakhxHi7OrB+ndFO2Y7DErB.slDQYFsBYdFoGp...H.jDQAQUlYdXdd7FuIqahd7fYLiu3G4iEY5bjMsE13R1Aabk6kcs88vdRGzmyuhjHCNQRLwVP65bKnc8qdz3NODd.+2pbi78huyPB4gcyN3nbPpI0grIGdHdx2esr7kmAYjoAXdGbRf4.LLivX+Bym6lGDSXhbIGZFsY.wQbQcBNwYLB66pvnRz4tQuIZhgKykKoa8a6CM2H+2Q2J7DErpOP00qQZoL4qFeOkFLg.+H.tLW7LqjEO44wr950xJ2rdmGElyxYu7Y4radsr1MC7AMmlm3.3dG5CxSMhsHWe0Or3P5RzR.jqvBaUtQpKIQlbEpF0nd2Gi7Iee9WumA81.3pQ9tgHXsWwdX6xsPqn8jMYSnDZDoxfF3D4icmi0nDQq4lTlQqVVYhdwsUhGDjMj4KP9U5Y7b2wSzGVM1HLRmIE7tT3O..7RaqexkyO9gOA2cKdUdtm2UHVUT7a7a66exK8ZuDOZKBkv9bixtag0e0dTW1jIoxc7BIPBgaT12NqBsdsntvg.8Oy7vzUiIq7nqzaCQLzEx8A3idMRSjMmFPSHuR7.gjqnmzhcn2wycFONAKgf5qmm2g7TcnAXgRtMr4K9gEx63uEub+dIdlQse1+wzy3WVY2r6ytU1xeRXP4C3dYGbYtDlwD4iUhjHic.LDitv4YUJ4KMJi8qrTNEmvdLYkGIRC5XxjbiLJ6av3iPv8YDFpOLH7AeKw+3pILz5quaIdbBVX.c5Fek9PXDdIdpf9gejAmXmu.OT2lKe+B063Z.bQLnfx7DjNmfigW1iNfrHaRg98XX.qHnPLUnjc7RIg.3zhyv5XE3q8XxxK7wqdx.LDQAW.cGPWA3pDHJYDzQ5N4VxQ19IygbmqdFOOA7DErhPuFvDbcIobQg23CmmyefWjQl5uwu41DSKR4Me8SunJuM4Ixm8yNwrcAq7wBwSMaPeY.c0vlrZbBfevnL1Oy7vJ4aOgnyg1QWt65h8ip0MBiJQm6DoPrTMxuD1Mf.4z5Gs6RFwX5NimnfktCzwbDV3RbALWLu8MokIaY+t7R2yA3.+gdGOCl0Sg5RMkT82xLlHbY3TaYsn0x1P+kChGR9jj.045BBw7wJ8hzL7UrHkFWR3tEVOGj8h23C4S9TMRnNIwf0kiscADGZgyPYFszmWPuYfXqDDqjHsYCwWpmwySAOwSITWmruijpc+raZIsibJh3ZweBfYyTd6kyx2ndFKWDmE3.TfUZ5qzGBf.HTBmHIJhgpPrDOwRUHZpBQQLDFQPPDL9i+XFuQfIxibvB4hiejlG4Rin48IRhL3yxY0813J.qDX6nyCLwwIbtL4OQ8oQjK4R9XkdReG9bY5tCaY2A2E5L9y.ngxFSio4kX1WHg0zKZ9Vz634Ifmnfkgj6Lqjeg6f6GSHtNmYZFybAN2I9NljgV1ZLRjRFuPvxkRNHvAaKctNuBu0+mW3E9h+3scAIrWoHbTPbzJCNVH2qK0Ntl9uUrRnDUbIS6ayBYd+hANky2dYmwPhp9kxOx8xifWWMlrZU+qE0J1CwgxvHruNQXOUbzMox.we7uzD6UFVVE3tim3VBMj5F9FDqksv5wOB35ttu3GafecVGjCdQiXbbQ74RIuHvGC7Sqfe4iNKmZQARvXEKjEYZuT3bExlrruRj7uZovwYH.ZIsyUTRkmJvULBCc.wA32Yi1SHZaDDgDRuHM2kNFcaPmEvPIPXxPoyzyhbG.EDSX5L4iWFVoo1cGOQAqz0qADnsZhOl2kbHa7p.KzTfI1LqwiqNBMY9j+kILo6xfS9Xgjnwth7zKcf4oWi3X8fKl4hI6+5adjKcwMIlrru5JcmPBcjtSbjfSCVT66FXVoRiMrNus6NdbBVRIFxI1I.9cw1384efO3KdgWXBHGxRtONvALhwn7jEx7VwAYuazacFUB4S9TEhuQ0kpDsAM0tJFoy2WMKiSR53EdgExiZShsMYRt4Fk8KiDJZEpuxLN9yMZNa2Ygci.IRVHy9VlsCBdfBVn47VCAAvbDSm+M+cDHvW7GaXMur4htpRHrqD4JXweqe57D9shMBgvCqZzHWQ.YtbfcpWiH.Nu3BrVV1UiIKS3so9xcYHcjFcPZ.wpWiTOY8oYzZm5rcuwGND6cieBu+5z634Igmnf0NQqpVZXLCw2velGi+fCSXDl2ASvFcvSVtvFXEKJOxypImriDSHvDlPyA89f+3u8pMuVovwO7EqX8x0l54JJixVjRljQYrEybIerfI60Iq1RWFRbDW.k7S5ZvnRz4dy.IPBzoUPD+vWVByehT9243pPwS7TBuDvZ.FnQXLGezdMhUxtjClQxyXJBhod.6xHre4IajMtmyPFGNBhtNlvFBLiWXFS1+OGmWX1j8ku.m6rWhyexyw4+iLH8ibZNwgOMm3noyIN1k4bYXEqtpVB12B72ABTuF52Dag8I2EIRRjK4RLDaBsitlx2yTMr.U8lfFfVa7pLiDHDYfzM5M43jUWYBSbYtzEVDyeF5Y77DwSTvBojuWHLFAKGH.tf3h7e3MvGoWerPPajRlBFvVXJGwxevQ2ZzDWbmkLN8k3Bm7TbpicZN4QNIG+vYvwOxY3zoeVNYFVvxYNBGohnle+G.K.Xv5wHBz721R4GoQzrqdRn8j98.UDBV1aPp5tJn1V5JwSMIKJ9JDiu3Gqgk8CYPFF5NM7DvE2COcYDoPvdw.RSmhBsnLFPq1VsAojEB7KnU1ecq8uUhjX07Bu75BbgS6BamW5kdKD7S50HZsr8ZvD36wa71dj8Ky7Q3NZP4bRp6mPvN.psdLhD3+J+T5.8vo0ns.IH9q7Tc6mYgKWOimmHdh9vBzh16uwUY7Bnh6MPGDB9GBA+pPv1EB9Jzpm7tptNitXeruz2E65HtwhU.rTfcqWiH.Nh3HrEVucmuaifHn.SgAXHkj3aB5AFfXUcj0llQacZUE0a7livA11OyB8j6.1kY7TErPJ4CfRt02ZvTKfgIDLIgfeWHXiBA+WzNcn3JmmKdxXQJwvJzbKl4d0jYWKlr508S43uaaTNaumL.BgPvpSc1terbVzj.cz.B7fwiUvBX+.iuBb78CsHZ94DBlqPvNDBVJvqgVoEwnKFdU1XJXPaudcrRNNGEuwaxk7nlT2V1E5ogz8oKEDOPe0iAj.AJ8itSpNsH8Y2Y6WYQLmuSOimmLdxBVHk7FnU9RbGHbftIDLFgfkHDrSgf4A7h.sCHnJ1omaGGECnYIH.tn3R7qrT7A+..yXRjBoUdE46CAC3DOaMchZQcIWmDY69hurS9s4uO1mty1COU7nEr.NsTxyUQOIJFpBP+EBdWgf0XeEXyD3Y.ZAtg0voxaLxHeewLOxibvDBxgbHY5vcFIQp6FsaIfIipl0mJCDG0RjhcvvLKjYWouph5L7zEr.36.9zJ5IQofD.tCgfOTHXyBAaSHXhn0UYpSE7bqhheAXuFgg1tXarG1A9nE3qDEQW0dPp8wHrsSnc.5Jcfj.IHSfjoCkny1ONGY2yiYuT8Ldd5TYPvBojQCrrJ54wMI0C3AEB9J6m93ZEBdKfdADVE7bq7h7LBmu6HY1WBK.usGJTVvB8j9az0n9qebMnpJZOo+DZITxt0b19uLYzYajySmJEBV.4HkLXfxkNYiK.+.ZKvKKDrH6aebF.OBZsJpJyLEnT1q0JAVNKhyy4vLlIOxkFPS6Y8o90zHrcQP3.2tdLfDshuXOoejmSZ+7lvDWgLy9GYFtrP4wSgJKBV.bFoj9gVZ63oSUAtSgfwaeqiqB3uAjLXuW1W4gCC5OHRE.oKRmMwpuZBQGHA3ee4NFhtmgEMCDHJ8ZjVQ6nNT+qqTUWXr6r8EsG1yg0634oSkIAK.xPJIUfYTvFtfGN9AzQ6Au55s6+q2BnC3glZUEFoDCqeKtnBTxsxgbnSzighKPj2n1NXpLPDX1o0wLuvK9Elq6bCisbiJaBV.bIojAGhLnWKDYfUVDsJHMEssN9q1EudcflTQOozI+LZwUmtYCrJ9CNDdiOXAKTcpUS6E8pcFgsK.MFni5w.RfpJii1PWbZK7xK7hSP5GbSrtEqmwqxBUFEr.fKwUd8GgWXlcP1YpDsZqBSS.961EtVLZcZ3JrxqhNHWojIqWiH.thHKVE+BNpKXRfdXvwjkPv8iAr51tSeIRhzoNa2e7mUxRlREThp61QkVAK.VFy+Y9mLti+Wk+KRPlPkYgKu.RQHXJBAaF3owyS35qwfR0pel4Q1jMlr2jJZAc31qA0vnN4U+Ata8X.IZqbJERyok.Y6y+79Il4WqmwqxDUpEr1Da5De.+iGXnLRqeNyhQKeEpirN2PSEsRF0WHXbBAqGcVtdKm4f.KxHLzNE6fcw1v2qFSVQESGna82HrMZgcRM0qQZgrUTOZnSSEGevW1AaYIaisYHwpVkAprchS2.6gccvbImSzE50.ZJsjTX.TeRBKjCmlSfEw0VNtmZs1oXHFgfgHDjDvpw.ZW7kCjoPv8pGC3HVw8G+nyjB4QdHPPPDbPykYn6UpHD71nUr9zEifmljnoNMbF7m.XJ7YuxNXadR0jMWJU5Er.Xyr9MKw1kZAsqOfjDogjB8mtPJDKUgr4JbFwoutUbUIR7pwBACFXGnsJF2YNpPv8gAj33miSQuYfWcUVQSrUeKr5u6jbR8zgYRPH38QGEpOIPLxn4Y3ufYLWrkAYyXlyy4N1GvaNpLIyaoCVzBxsDBV.rYV2ZMgszSlN027HOy4QdDEQSKoCzGFHcjdPrDKVHat.mCqhq8KRUBDuBUH3d.x.XSUzSFmP9BAQBzU8XDMmumI0mFR8oQjG4QfDn4bI6S+qr7UnCS+nBg9ZA8.zetc5ICvoohS.DHKgE7oKf4r.8NdUl3VFAK.1DqeyYver1VQ66VPDRn4PNXg7P.TEpJsgNRuXfzU5EIPsvLBtLWjbDWueF7PEvLKDL.zJoKqthdx3DNlPvigAbJbVIORgzHexGIRhjnpx2wjFO3jBNUwiYgfOBczUbj.lwDih+JQQLjO4Wj2mIDHPj+33MdxiywukqLH6LtkRvBf8xtO3ZXISuFTmZTaRrgR6Mlg7Ie696.hhXoYjL8hzHE5GMkVPnDJVHGtj3h2PP94IIfIDzKfyAr9J54Rwv4DBZGZ4Zot3LbR5J8lvHRrfEhjXh9nr+kd.12gKClqyBAujdmSMS1bFNOI4SdE6g93K9wdXGK+iYrumdGuJabKmfE.miycoEv2OsbH68kH0uYQPTQX09eEVhVhzZg7vFVIPBgDII5LoPeXfzU5M0lDwe7kbIKth3F695t6BXBAoBrULfxTrKhrruE1xLBf7D4SLTERl1SdjGdiW3E9HWLyaN2z1SvXPqr.oKd.dBZLsnDb1t+707o+8syV2ldGuJa3t+YKWN0lZG5cvvdh9vs8TgQDwmCYWrwFiYLgW3Mdg2XCqbdNGGl8yuylYarI1K6fSKNyM7bto+P97RIsACJByMX7WHXmnyvGPBz.YC3SX5.f.A4Qtm6AX.063b7al1XVTBA6AczzSj.QJifIxbHLhnX2NnYLStjyIuG5c8OGm6Rk0wqxJ2RtBqBx4474tZV9pVJKXRYyUNdUnpwEIwTEuvKjX09ZtzPh7pq9JexGewOpFUmVR6IE5O8laiNRWoFTK7G+wB43NuBL+EBZJXbM1TCj7EBhBc1m+.3LhyPxzdpN0j7HOBkv7+LbhcuU1xucSXl6SHzWvhBPeHMRk6nDb1d.rRV7DmOyd15c7pLxs7BVN3Rbor2.qcceGe0DNIG8W8FejQSLUMDBMPGMgTYg75fDI4S91EvrR.D.wSMnEzd5I829oO1cpE0k.rKfcYwMFNTUbBXhZ1bZt2mjStjJroPwS51c9dY92Qc7yUewa5L8FKjGl.BhvCcN7ckZgZgfO.sBvXYBs1Fmfmk+BUg3bpy1MgIaeBuyScTNp6Ro+1sB2j+Xu6I0lZGSmn68tcz86r9zvtFBgEtCmy6r7+RCAlwDdi2XFuvFV4hbAND6msyVXarA1M6fSKNcgdpxOj.MT1PdBdoY7975O7A4fWrbb3KQDBV.FPCdHZYT7kLGBlvvFVwa7I+mig2r0y5KMAjYSsmtSkYgSIPijMlOluCa1+uhBewWNH6c0CiaSWIVckYTqvxIbdNelaksrs4yr9t0wxl7evg2hDokPIhHBkvB16qF+fEdsWW6pWaEX4iO3KUk3oEzVRg9SuX.jLsmnIVrRdbQNe4Z7eI.Ns3zzV5PCeXFU22Lqd9mgybi6gshibDBzU8rR.joHKpM0iFRyHOxC+veS4hkyuJVRIVtgEBddfNqm4..2OOBsj1PtNIUbBj.4a4K9GakM4oVHJc4nVgUYfZPMBqozl10ZZSpMhl28pP7MxW70rE6hSk7pu.PfWXFuwG7ByjEYwQ3frYVKqlkxuyVHaQNE3tcMHARRlDeIyiywY21KvC1mcxNOoKZ3tYI.6NeuF5wHRf1K6D+Gl.4QtXBybNNy9GDcswfSTPL.m+KABSFBSj4PTDqSOPGKj+YePFP8NFGSOQiekZTqvpLvE4h4rW149WFKdgSiIO9sw5l4II8cXCYNASngDBgDhO3KlrmYaE85u.aXytDmi3+JFZFISuY.zM5CUi34JbQNs3ZwNnqP35rhyRqocTOZTrMhVzoUvh9trHqh+b2K+vhPPLX.qv4rjAckdSD1iIqnH5HNNGdU6i8b.m7XoHD7z5cr6Aox.XHjiSb1t+3OqgkMkYwTmldGuJynDrzOxiywO0lXcaXA78S6GYlSX2r8EddN6gLgIqARvgDDAGPIIfUv3+RhMBiHoUzV5MCjlSq3xbQ9CwQ.LVQKGIKbrDKsf1RjDU7IRCp0BX1yz.GF8fg37cKBqDKwRqoCjG4gY7BevWS+D+vrJ1mSK1qZZYcbc7uxOMuLUkpS9NoTx3M9vGw68LGgCcrx53cq.psD5hotT2nqKMnEMkV24jnIcrZTylFJgFIHHerP9juS2BoILge3GRjrXlKeHuEmQbFC8e3j.sR1ZFKSFqXgfHX9bF2S9I7e+XCbXJyHD7S.8VO1P6.FZDeLeGRjZhXj+EeDti5eHNTFEwiDoPvdQmwdU8j0mwyzADEqy18Fe3Xb3Mcuz21PYKsgtkA0JrbwbNNWV6m8dfekksz4vzlzZXISbarwe5bblCZBQd9h+AELgDju3GlwDxBE9DRjXAKXCqzHZNsktv1XibVwYMTQq7Ha5C2F9SfjG4RSoUcdirxocJN04MvgorRt1q3D5hyINKsmtRbTMrfEBgP86BbtCrIV2FKha+1sWYQ0E2Kifjoikny1mIe0+ZSrd20zkxsA0JrpfIdhOh5RCZRSn0cnwzrtTKRrkgRXw.B6gOgkqK2ECf.4jbLFEO.GQbDC4e.0hSH3SkSkFSKHGxg.HPVGq7aGEOz8Y.CgdIPgfcATc8XDIvCHeDdZ9KbYtL9hObH1+pueFvMDFABAyA31zyXEjL.lHygpXWfrnvLlHerdwGlau3VomhBfZEVUvbItT1GlCdj0ypV07XlS4WXdSbWr0EcVN6e3O95UnDQDAQP9XFyHQRdjKQPzjHIwhYtjuvptEsb3GqjoCTWRBK1+uZQcZzdYqy8HbjJ5SMzhPPUPmM9A.tBWj9vsiYLYuZjFS09c1xbRm+nfhEwID7e.6EF9xHckTXPbeNMx18C+YyrloMU9JUYPtTPkcAqvApKZMozABDHt4EwtKykyd+r2CsZV1RlEe6WrYV02dTN3lsgLmHHxHBlPCwF1HApEmgSxNDayvVlbSn4zTR9p8HOuwGgu3uOKl4eSmrvt.Ntcmuqqx58EDWf1QGopTCrfE7A+EVwxUVA+RA6JM2kdi+K.dRdQRfZ4z51tu3KeFu+nKiUPha4nxvVB8CHFzhUm5HDjHZkljZCDOZM6RG+R9TjR86WhJJzh+qVzotSeuyVR6S8hbgpLL5KWRjot+GRIvCJeLdBdIxzd0TVK1frdgGm6pd6m8eZmaAWO16LPonGaHAFp7g3Y4uQlbY7Bu3RbtC+3buM7XbrrsONyEHM8LF0VVa9LlEdgYrVrNa2axfi+62EozBnTE7d2xiGQi3TJklqV0pVXG+3GupnEDeIJDTezV8TMApBkttDS8cYSxxANBG4BGgiLu4xrmWUopQ1atszhhX+GWhCVlyysBh1VWtl+xrhMBkPCqUz9dse1eEdaRWJYBBg9Dr.XsrbFAiBuvL4S9DKUqlsfj65w3XKDseWR2IccJL.BgP3xNoT56G9wx3mlDJwpRMdDcMmt0stL9LxHicKDrUgfevt+EdTfdf1JoJsszpF.DmqZdVdxw43m8K4SlzAEGb5F0xjsVDIka9jOslNp6xBrAw7.RWuF4fhCwdYm3M9.nE+a8f94Xk28.Hjxpsk.9K8itSpNsi3XBSbYtzUVHe+2UVGqaEwiPvJzPCOeqVsFE5eKrAgl+rp7fj+vnLk4hvklVHOpK0qMf8OcWwxU.9V8X.Ggt6ZYY3HWPykbnIjbpwQbAf.c2NvZCcjZRcIWmTj97E+XarkEre1uJPQuIviPvpScpSK2nrkPT18MgaJYYTFxW7mB+2DrgUhfXqQinQ5JjBLJjRlDTL0mkaBVGqfrHSLgI6a8MjH6F8YDni+fliMS2GFHhR3us5ElYYLuITVGqaUwSQvZ8lLILpVcT+.B1frk6.FVGdNrhHntsA3G94SBT6ZaTiiNY6.5oy2..6WrOND66pqxxFRpOMZLnyDsNAY0sGnnEenL3Mdww3n6Y1Lykomw5VQ7HDrZe6a+AiM1X2szXZUywAW+x9ikXCLNOuV6N.HD5KXJKHwPUPdCmnkDSHHbhxPbruQfThtVYh.HerxF3WwmBrS2cy1hBcdPT8f9QXDtSS2J+ve9U94ICNYOiJJR7HDrDBgMe7wGCopXJABmvdomjW3EeaF2D9Bl9x+F9occu7punQX+J.ZldMfi1OUbT8hzw61PRUo5UQuiiAxbANtdMx5Xk1SDZyjIWlMnitelDvWo2jB82oMXBSXhrHqbVD+PE9ot5IhGQXM.fTx7.FkQXqLIyl2XZQy6D8jKyEwLdSCnQIaD1tblnAZsQXnXjwPUnZEa460G7ILiXbLHtLv2A7b5wH6lemiyePBTa1N+FGVbHcMoZEsi5PCb51A8EeYir1eZarM8MX2hhGwJr.vhEKqF3n50NZs+IKLNdSNGmwd+HLGpBw2n5pyTwnBfABXHBIIRR12JSwUr.r4uQLNFERIeI5H9kz5NzYyuylHHBhsx5wJ1z0wP2GFHlv7Mz2JKHdg2rDVvWnig4VZ7XDrNwINQV.FRmDQ.rKwtXpLABjfvFVIJhNgHniMvHre4DdIDFyJNAnkzdLgYvIeXyMisArJ8Zj0ypHexmMxZJy1PBTUYbzV5B4P1E684EdQFbhCsYVyhJyC1s33wHXYmIiA9IpIxGwF3WweBDuwGSskN1Six1kC7D.MVuFQy2K9PxzQx2o9.1jyJkvUHnWmuCvNYarO1E6icoK6zMRkHIJm5rcewOVEKYJGgiT76YTgSwSSvZi.+pQXHAPth73M3Oyw3HXBunoj7.MBaWNPiDBdCixXsfVQsntNMIcsPttC0EqByb.zUkjHCNAyioy4Ji0WLIZqbpWjlS+4mIDXg7xa9LaUUYPG3oIXgTxGXT1R.jtHc9q7TbbNJsfjaeKnEIYT12EQTBAeG5H8QJL8k6xo9dwDBNN+gtOUNW.WBnLWCzc3OyYvjK1pAZoglKaI0iF4zTwwG7icv1V5uyF2SYdfT34IXALGojsaTFS.rawt3E3g4TbBuuOdzG1nrsKfHsWX4ZjQXLGUUfNQOcxIaIvJ13Dbb2xS0RJYhnyxJ7UD5KYARkAgW3sSc1t23EKl4nhrcchmnfkEf2vfBhT.MQq8J1MOL2E9g+OXqnUQYbV2vnN1qs4cvHM5cyCQPDRw56ESHHKxJ6L3.62HGWCjeCc5lfx5ICp0jVil1S2cZnL3EdQ5j9wVI+xBJiCkB63IJXwXFyXldspUMWiQKZcbQ57x7DQjIYNVfPMNqqaFjPvJAZkQYPs9QXCoOLPxgLK16yLl4Lbx8sCNftqRBtJLBmuWVoazahgXK13WCfbIepMgO0LHih+GzJJU3QJX85u9qa6cdm28EvfqiPZcI3rY2hcOTgf0CLBfJx3OJIgfIKD78XfkEGsZ3tfGiW.+H.mD6UZczk8vNVEt2cyk4.bpR7tLPbjc.8hA3TmsCfEx2Zsdu3lT4yLqxMdjBV.LjgLj0bm24cLNibUVflnk8sHTOgfIHDrIfWDs5tU4Al.5rPvWXercIUH0AJGLsmtQVNY0Uflv1uxxluqXNXfbAzgy2KqzXYyHIZpSc1tcVYvuXjFleWuUFOVAK.F3.GzqBFmC3KFRRH3cEB1lceHMZzRGFirhOTEfdKD71BAaVHXE.ODtfU24vQ6ON+Im15o.MeubFNU5ahUq6pifqFiv462rzGFH9feN0Y6.XCTQ1tAgGStDVTL7gO7LAFNZQ7rqtZKDHZhJNZnmGCXO.6QJY+1+9Sg1QsmEZYhuMzVvlWnU64CFMeiEGPBBA0Csx1bcvfRwFmgDHPo+7W3sHLBmrJgRoku3GKkebZmlSeEW8by.Xy.qACny5TRHAhTFNchdPtNIx10tWaY3KxevUOmtUAOZAK6rEojGSHXxkyia71+pmha7XlxGM+q43O8ZBseVWgshVGSj+DuFMmjcZsFGtZfNZ4G3aGuqe1YLHk7EBgqWvBfNQJDKwe0F1QwiX58hVewxi4zsB3QukvBvWKk7pUzShBfWnkH09Y+KevMPr5YkuDowf4xTxKXxOBf0wplwlXS610N6LT9d.WZ28wwAVzatMrUBE9TIRaBL8ktx4ysZTYQvBf2D3cqnmDta3Pr5oj+IFJOJYxUnjRGSSHvJVyapL92zkOAMVNOvLb0CRRxFRioEknOTC.tmG..XAxIQTPTAAVWOnoaxUOetUhJSBVHk7R.uUE87vcAs7byLunbLLbdRxlrJQGDCPfDDKg48wafMrCW+rzXwty2cokbh9v.I.BnTjNOxI5JmG2JRkJAK.jRdEojmWB17XJTJt.bDE1us7iYH7fjMWoTkubdg2bZN0Q+L9fW20OKcIrQf05JLrDHTYHzE5E43jHaW6dkm0F9NKWw73VYpzIXYm2upxXGZ0kwKk3AUgmL.b79sMx1w+GeMcldxk4RkpUVAf+3Gim26oNJG0cr5LTZPZeUVtD5HcipRBkXvhB788hFdVW073VUprJXwwIiod6b+uapRst5UkcQKGBUgHCjmR9h7uYBDO0ztOqJcDLAyBY1ic1Ly44xlnkOLK.WhXQuYPkpUpZCSpXuxEfQ0zfcWwqug4uv8xN64Gw6woDZYuQko2zETHNEYeYD7zjHIQVjoSS4lBi+D.Gj8rjgRZ8kJAcyEgfOA9+au673ixpyE33+dmYxjYxFaIPBKg0.HjTBKhKUABAYw1Jn2a4JXkpdqZ+Pwp0p1ZUqEaoTpsp3sKTU.Wp1psUTAsBhf.hUQbiDjEEv.ACaIrDRxjISly8ONyfSRlL6SVe9lOCDl488bNYB4Im2y647b3liUkmBHG0P4w4ehgmLXQywMpOXKLpwuPLZKublZWpCaOr7v08vBtlIykummh0vbUWGooRgNBWlnueMbgpKgkpVI+RVJ8mASkTYXErxF13n7k67941tZ5.DrBhOC99T4JHYRIDduU8jRvp3iNRc1nYkK4N7Ghmb88hr5ytnHVMOOqi0vwM9porS6g2H78m9RTYkKlIwrXNLNO4i8ZolPdrp7xF1nJp7ytGl+z1FaqMYNuJBYXXv6BL9nsfT.onRhUxKQlzOpK.wzUnNsBSCaJ70NZzVuhlp8vOmFSjO4OpeMK6Uyfd0G23lixWxVX87lrF1gwGiKeR7CskdSowgeFrZvLAlJExLXvnSNpQRfJ.Rhj3XTVQ+JtiY1AKXkW2rmKMLpn.lhZ57q3ODzEKtab+LSgQOunsNE9Waoe1LtKexeDKlksptROFZc3jDwFNoV1G6g2isv1XK7YrKNiQSGn5Vp2nZbXGyXv.UCgwwExEwjYjLJ5BcEm3LTl3hMqTIM1MEs96ma6Z1O6uEM0rzBJcCCJB8hKOh386GOnZYboLkfFvpdbWvkwneqHs9DAVmp.V.LLFVuuWdvmY3j6jqjyhIz47IKXEmTKGkCydXmrS9X1KEyAoDJ23Dg0XBAM7M1vouO1UIRVzGFLCmbYzjKilAvPHERE2TONo1vts3KKXA6Xm0xpW58xsdmPvu+7sm4ICaL0fdfMCc1sXf73rJrf4.9duB2EahSM5Bnf.ulcDQrNcAr7v5h3QV7T4JtcG33byoFSXfYrPBj.FXFmTKmgJ3XbDNLGjCyg3K4fbLNJmlJ3TbRpkZnZpFmF0Ez.IFnyfmIorSRjDoQ2n6jNYRuouL.xlAReY.zSxjTHULvDtnNbQvK6PQxjBUxoOzJ3Q+wOGO4+HpKv195mmdXEwYOVEvMp9gbSbaAcAiqPcmER9+tHstDAWm0.V.vLY1eqaha822SxJmpnplL+ZLgAlvDlwBlwBFXBPQ83Bm3DGTim.VUQs3.md9nNbRcTqmEJKXAqjHIhURDqXijIYRhjwFIgMRDyj..3F23BW3FWwj.Td4sN1Jqe4OFO78sa1cYwrBuss6vvfGLROYE5d7tBVE8kAFjAa2cUlvzvKfQUZjVehfqSc.K.xlr610w7uqB4arfDwdJNBo0amNzkAlv.COg0zeFM3O0Td9v6m61yG5OO9MIK7Fjb27Ia3Y4IdfWm0ro3RE01jYOYr0QEoEfBXhpB42vxnFpg.88IEp+Qgj+riz5RDZ5zGvxqww3F12g4+iGCWvbSDaI6fZB3t3aaUlvDIhML.1G6diuLO+C+B7WWcqc6pUvEZXDE6+7nCOsX0+GEvLB5fsCpoOYxesQS8IBNIfUijO4myUvbtgKhIMmtSF82Mth5A5NdyDFj.VwJV4rb1SWDaeMuFu3i2IqGUMfgA+AfePjd9JfrU8ikyKgURLf+xKEt2a4jPdylb6PLoaaKSBX0L5A8H0IyzmVAb4yNGNuBRitjtBE0gSpGWQz7dJVxLlIArhYrPsTSs6ic+tak25e8N7lu7mxmdvV0FWquTMLXODE6zPJf+W0746ycDBC1t66qPF8uJRqKQnSBXEBFDCpm4xX+5mOWzTNO9ZWb5j4vric6.3l58LP406yXRE6X5biQlYrfErfYbgKJmSTZIr+2+iXaqaa7VaXGri8FSq3129eLL3uGomr2Aae4rJ5OCjZCvfs6Fki5gQLMxui3DusMGIfU3yHOxafCfgl2vXj42OFPdYRexoqzi9jD16dBjngYLct.W5fXg1XgoCMYFvaV+zMNwg6po5STAGujRozOcer6sua9vsWLEuyxo7fkPw6TxvfWGXZQ54q.ljpPVbHLX6tQ8JSg7mYjVWhviDvJ1vHKxpG8g9jY2Iir5AYjUFjYlISZYj.V6dlzmTA2I6Franyu6VRfDvEtPgxEPslvT0Nnlybb9xS5DWGsLNXYmfSdnivWVZ4TVYkRoUzZ+EY6DC0ybuxZjV.Jfeq5OxDXZAcv1UvLKjQI6JNsP5Hrq4zVfpLJ6DkQYmf3+9jnH.LL36RTFrZvpAy33RBksvqCXhtttHstDguN5oWFQmKIQLXmxdFbUjJoFv6Lrm4c2yV.CLv4JYQLkzCKQGIWAP1Q5IqyY6oPALifjy1Mndb4zM00RuWX1omzCKQGFFFL+nsLlHSm9R+CXNa2FVYurqMbYbAxclsElDvRzQwWG3RizSVgdts8s3aGzU3PBXk0wpa2riX2QhDvR3OIQTjgCZMXXvcDskwXUmOij7wY.tbPKXgCyAOv6ya+5Qa8IBeR.KQiMPfcCb.feNsO9+HiC3aEsExrXtXByAbx+ZG6rYV+yTJkF3agnHtn8v+YTDaYGXX.i.n6940cidKe+u.TIvba4ZZQFCC9MfmYbaDPui3jCWLSJfSkASXPMTsi2fW9ohz5RDcj6RXmG1A9w.WKvfP+KqNJvpAVDf20eXIzvTxRDmsNag7i.JLZKjYwb7jfCa9EOPhXm2ms9pEQQ6OZqOQjQBX04PWQu4hVPid9r.tIfoidJA7I97Zl.FIPa4L9vLLLXIQSAn.5sJKlLeSOKCmlmILyqxKF0apEhHmbIgcN7vzzfU9JafmEHEedt4BrCf8.z+3WSKhMECCddvS5ZMJLKlCoSF3hlOUrm.VoD97crVdkMFs0mHxIAr53KWzWFXvLR.eyXleHviA7b.2PbncEMtdCCdEfTilBQAjtJclAWYP6ckMrw5Y0KCZGlUG6.QBX0w2DIzGPZeGupOE8V898Eg0qwXG6XSOBO2lS+LL3IMLXEnGStn1UxbHS5KtBvDE0Ll4jT9wVKuxeKVTmhHmDvpiudFFGq+BvXB3IB2Jc5Se54kSN47TSdxS96EtmqeLXfegmbz92MFTdn.5opmbEb0TCUGviMIRh2gM9zkPImJVT2hHmLn6c7cjv3X82FpZc.GJbqzcsqcMnRJojK2vvXp8nGcedm5TmdS0We8EArefx.NEfCZ3kXk.5IsZ5nmOXiyvfBPOK1SNbaCAyUy0SljU.uyflvfpoZG+C96xfs2FfDvpiu0B3hP660g6r29aBTJPN.aAeBN12912O6jmrB0YNSkVJu7JtTCCtTiuJ6qUIvo87vA5N7XA8k40EftAjXX1VBYJfgnFByjqlpCRuqrgc9Or4Wbm7A6Kd0dDgNIfUGKyBcuQ9RfS.TNvNAdTfaOHm6GC7OCi55tQO+slCvy.7m.tMOu1H20t108USMNvv+oHxT87nugQ8EScibajBoQUb1.bTFTO06dU7TORKVCSDPR.qNNFO56nWiGL5SA7f.uD5.Z9y9POMFBb2M9JIC7CQmwZKBXI.+TfWF8cj7ppnhJLAXzLArZ0n.tL0LXhLMpIHYSTaXih4CW6lYyueKSqSDLxft2wPuv+Aq.8jFcQnCtrDf2FnJfZQudAWJvk.rqvn9FOPld9b6.OD5K6bCn60zTyKu79lImbxtTstatPMfBHCU5LetqPZmOJArvZ3Eh3cNZQrmzCq1+LC7jnuSZAxL8bL2Cv6gtWRGCB30D4u5ZvPCx6TIhdsGdS.GGOiCVd4kW2TJ0gJt3hGXXT9wMdCMcKb2zaxNHWJHXiDYWTza8J7hxDEsMDIfU6eKF8RqITjK5knyh.t+P33S.8.pOdziM1E.LTZ3.h6cNd4M6aNNfuec0U285vgi31.mGI9uUygowrnpftKNqmY6u.qP1qAaiQBX0912A3NCyywL5zFyj.99zvKEzF5.RiGcxvabnCX03k+hSzCl+V.9rF8ZyBXjm7jmL0xKu7X8DGMhn.FiZrr.tap8b2TxlmMrwN4iW6Z3keyVjFnHjIArZ+Zr.+4n37m.5wy5dPOWqlL5.TCF+Oy32O5Kk7MA1J50XXi+I+jPO63+2VsZsxTRIkpO4IO441AaTJZt6ZXbiBn+p9y8yCQBXkZo1.d7d13Zqekrz6skoEJBGR.q1mx.8frmRvNvFoRziak2w6p6z7A8NA50S3FQmwF1Azjqkp.zyCKu8xZVnmzmUjbxIWwfFzfNvgNzgFcX1FiYT.Yp5EKh+.8hdGz4bE.1IY1.u1J1DaZ6w+VnHbIArZ+wLvJQeoagKq.qBX6nmVBWrOuVMn2SE2L5fTaGc9xp4bY.+aO+suArdIzy+KyVsZsUKqbpCVkI+F9yLDNuftgnB5zebkb5i8X7PQ55mTDmIArZ+YQ.eiH7bSDcR76lQOH5WFvLPOWpdaZ53QEHEfN3oSedtODcPurSJoj5+YNyYNW9Zok7xA0yj8b3A3QXPLrPJXE.1IIdBd367.bf.EnVzJRBX09xbA9IQYYXfNsw.viC7FQX4LR+7bdSld88PG5PWU0UWcxfNXUKAuUyDUSg6hER2IiPNXURjLuOacUOMOwSG+ZghnkDvp8iw.DKW.tKC8kA9WCgiMAfzPuF+x.n2nGfdngC7t2Oup8su8kTEUTQdP7umUdqzzTIy0wB3ay0gIHn43JurfENFkU5R3dh580PQ7kDvp8gzQOH6QRBq6C.VO5KEz2ueaBXEnmw6aAcfndhNsI2aOOxxyizA5A5fV1ZT46MbzvAlF57q944vgiJsYy1oN6YqLbRuMgEeiTNE0L354GvPYDTEUQcAXaluokixkCp96VBkDNY1BQq.IfUaedCrLrH3beLf6BcVQXS.KGc.HuR.3u640SiHammwa5gY1.KzS8bsSXBS38qolZV+ZVyZ5o2dXctKMz3qhxEt7MHUxJ6bwT.WIykQy3Qg6.lpXZNtv0sOal1FhvljnETarklpvOVDvOKLOmihd2jowYHybPuLdt3FeBgH2.eA5Mqh+Cv1PO2rbfdMENIzCh+PxM2bKst5pah6YO64b2MS61sWeptSQcbmmvhJHSdylSWToPNLBtPlDecJfAvP.TTSHLgP8+WPpGbJj+cEQMFQKNIfUaXlfq1cSC5DP1HgWOU55BNNG2u4uodQuR9rblGsJpITxS6UmHIt2THoOTgw63F2a2N1+rxnrfMglxrm8rm28oO8omes0VqE.xbHYs+a4Zl+xufENoqc+bjgWB6kuf8wg4fbbNBUwYwA0Pc3DSXBaXmDwNcgtROIK5OChAyvYfLD5E8AqjHNoVpqA2jxviB0epPx+GDwEfnEmDvpMpuG2Z9qfGcStQkVHdJ0doTvuXyrgkXfQP6pwjYp21FXc+VZ3xt4D8hd8oCfA7dCkQ8tifg+wN3zewBYggz.B8S3WNgmh+30eDNR9I2sjsZxoQ1UV0YSIuBF8F+Qi3Vtiwm93OQ0KTs9ZHgbr4oZcS83DmmK3iKbgAFj.VIArhURjDHALvDtodbQcgTlVHXTndjBI+eTTUHhVbxXX0FzKvKX85YdOQHFrR0M51GesbS+vGkk71Fg3uCZCrtGYdbi6Yirtan+LvOZDj2+IeN+cNel2wNJGk2i2Kra2mlSNz9x.poeLveZgeiItu2y8GrRKFl+rq8Xy8mNu+37NVwSo3rcgSkSbS89rDYLgAV8Dbxa6W44i5otnpWTMlB2JvzOoPxWRaLsCI8vpMnak6H+kxu6iBwC2wsycO5GhEu63ZiJLULEa8ConwkNco3KmK+L.TzLKpem8kc9FmEKCKh2W4iBtQUhAtmegLlWqUn5Ew.ROrZC5i3SlPXb31dW15UA7qiWsmHQtjqSf2o0tc3kaTqzLV9YEPtxTWncLIii1FzdonBCmi+cYKy+uveoKwq1S7gAtwf3cm7U390g5mzTH+aPBV09mDvpMlUxJ65Q3HWP3bNtQ0mml+12Id0lhsLv.yTGNvAGd0FT2yoPE1aiX9S8nvEtoNp+HNw0xqC2WRgL5YLYFylhEkun0mbIgswrU9fwfNGs2.Cmg+qOHewMVMNxvem21Xq2xJYiK+5o.Gw8FYDxzYbZBLmzY33U5hx+sYPO9cEvXc7Zr2zRjZxGTWrBtHEFi.L5iILr61y8DLPbipBfOOKRdaIh40qn1sjK4VQKyWUhVRR.q1XVOuxj8ySe37Hued4T9oqFGKwOuN0QcC6Oy8ckDlyaqVT+W1nnL17lR2R5qZ1O229E89zWNC8LnSqMaFfhGQwVOdBGp2tKwZ187TY0mrtgt2STjlggJAT3FCpQgQEFvQUtMUZ81puzrVVV9aSfUHDwYuM5orsuOVpmWyF58OvF+5derMhrkWSKBkRY9.pCz30hnPHZmpen2Ea7MHT8.muOGyj77bMWPqYzx0bEBQmYyllF.5coo2bjGyOGm2GqqkpwJDhN27WfnE3miKCfC6mi0aOxtnVhFqPH57xJ5sbKeC9bJz4kJ+4Zo46k0KDuarBgnysuF5s6ceC77bA4b923+.V0BLh3VKUHDc5s.ZZfmfsiNObZ5fz68QrLcJKDBQCrJZX.m8PC2R3aN2K9Of0Y3q1+AEBgHlIEfxngAbVXHdt1PmAP8WPKIeOIDhXJK.OCMcLnFdXTFSBn5FUFN.FUrrgJDhN2r.7rDalKU6tQkwyGiZiBgPPBnW2e96R4B2LuvERCuCitQuyNKDBQTKQzyUJ+Er5MQukaEN98MpL1XLqkJDhN0RD3eQSCTUG5AZ2ZXVd1.97FUVyJV0XEBQmW1AdIZZvpOEveoUlPwTZTYsCZ3NgiPHDgsj.VMMMX0S.z8nnba75O7litloPH5rKYfWkFFX4n.WSTVtoQCWDzGhve7uDBg3bRgltl+dMhMyB8Y0nx8mGCJSgPzIUZnmSUdCnTMvcQraqhw2oEwo.5SLpbEBQmLcA8TTva.ksid9REqjAP49T9+oXXYKDhNQ5F54Bk2fIahXetV227gUs.iLFW9BgnitMu4MmAvVooYNg6MFWUqwmx+oiwksPzljrQpFiUc0UaCXLM5oSE3WhdBildLnZxA3x74emEROrDBQDZ4z7ou3OAH+nr7yFnTZZu3d.jo0fnCrX0cqRzPoitWP064eq740rCbDf8Fk0wD.dCZ5R44KPO8F9anWPzBQGFR.q1wxN6ruFzaMXVMLLrpTpjMLLRUoTV.dUqVst3O+y+7i2J2LEBgn4oTJKm5TmpaJkJTRwxBgPHDBgPHDBgPHDBgPHDBgPHDBgPHDBgPHDBgPHDBgPHDBgPHDBgPHDBgPHDBgPHDBgPHDBgPHDBgPHDBgPHDBgPHDBgPHDBgPHDBgPHDBQ7x+OcPSsr3X1G0N.....IUjSD4pPfIH" ],
					"embed" : 1,
					"id" : "obj-2",
					"maxclass" : "fpic",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "jit_matrix" ],
					"patching_rect" : [ 188.0, 223.0, 100.0, 50.0 ],
					"pic" : "Macintosh HD:/Developer/SDKs/MaxSDK-6.1.3/sy/logo/sy_logo_300px.png",
					"presentation" : 1,
					"presentation_rect" : [ -31.0, -15.0, 274.0, 284.0 ]
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-70", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-20", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-11", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-19", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-112", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-15", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-12", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-27", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-15", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-16", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-4", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-17", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-16", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-20", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-31", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-22", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-22", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-21", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-23", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-25", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-24", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-21", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-25", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-24", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-26", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-26", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-66", 1 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-26", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-79", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-26", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-85", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-26", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-29", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-27", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-35", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-28", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-28", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-29", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-42", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-3", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-4", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-30", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-32", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-28", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-32", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-34", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-33", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-26", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-35", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-32", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-42", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-17", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-68", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-66", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-67", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-68", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-66", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-70", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-19", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-79", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-112", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-85", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-88", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-88", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-89", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "", 1 ]
				}

			}
 ],
		"dependency_cache" : [ 			{
				"name" : "helpdetails.js",
				"bootpath" : "C74:/help/resources",
				"type" : "TEXT",
				"implicit" : 1
			}
, 			{
				"name" : "sy.nth.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "sy.join.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "sy.sort.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "sy.prepend.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "sy.scramble.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "sy.subs.mxo",
				"type" : "iLaX"
			}
 ],
		"autosave" : 0
	}

}
