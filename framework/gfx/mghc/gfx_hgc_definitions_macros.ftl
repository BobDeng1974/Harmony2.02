<#macro GFX_HGC_CREATE_BUTTON INDEX GFX_INDEX GFX_BUTTON_ID GFX_BUTTON_LEFT GFX_BUTTON_TOP GFX_BUTTON_RIGHT GFX_BUTTON_BOTTOM GFX_BUTTON_RADIUS GFX_BUTTON_STATE GFX_BUTTON_PRESS_IMAGE GFX_BUTTON_RELEASE_IMAGE GFX_BUTTON_TEXT GFX_BUTTON_ALIGNMENT GFX_BUTTON_SCHEME>
    case <#noparse>${</#noparse>${GFX_BUTTON_ID}<#noparse>}</#noparse>:
        hgcObj.p<#noparse>${</#noparse>${GFX_BUTTON_ID}<#noparse>}</#noparse>Obj = GFX_GOL_ButtonCreate
                (
                 ${GFX_INDEX},
                 <#noparse>${</#noparse>${GFX_BUTTON_ID}<#noparse>}</#noparse>,      // button ID
                 ${GFX_BUTTON_LEFT},    // left
                 ${GFX_BUTTON_TOP},     // top
                 ${GFX_BUTTON_RIGHT},   // right
                 ${GFX_BUTTON_BOTTOM},  // bottom
                 ${GFX_BUTTON_RADIUS},  // radius
                 ${GFX_BUTTON_STATE},   // state
                 ${GFX_BUTTON_PRESS_IMAGE},     // press image
                 ${GFX_BUTTON_RELEASE_IMAGE},   // release image
                 (GFX_XCHAR*)buttonStr_${INDEX},    // text
                 ${GFX_BUTTON_ALIGNMENT},       //alignment
                 ${GFX_BUTTON_SCHEME}
                 ); // use alternate scheme
        break;
</#macro>

<#macro GFX_HGC_BUTTON_TEXT_INIT INDEX TEXT>
static const GFX_XCHAR buttonStr_${INDEX}[] = { <#noparse>${</#noparse>${TEXT}<#noparse>}</#noparse> }; // <#noparse>${CONFIG_HGC_BTN_TEXT_STRING_</#noparse>${INDEX}<#noparse>}</#noparse>
</#macro>

<#macro GFX_HGC_CREATE_DGTL_MTR GFX_INDEX GFX_DGTL_MTR_ID GFX_DGTL_MTR_LEFT GFX_DGTL_MTR_TOP GFX_DGTL_MTR_RIGHT GFX_DGTL_MTR_BOTTOM GFX_DGTL_MTR_STATE GFX_DGTL_MTR_VALUE GFX_DGTL_MTR_NO_OF_DIGITS GFX_DGTL_MTR_DOT_POSITION GFX_DGTL_MTR_ALIGNMENT GFX_DGTL_MTR_SCHEME>
    case <#noparse>${</#noparse>${GFX_DGTL_MTR_ID}<#noparse>}</#noparse>:
        hgcObj.p<#noparse>${</#noparse>${GFX_DGTL_MTR_ID}<#noparse>}</#noparse>Obj = GFX_GOL_DigitalMeterCreate
                (
                 ${GFX_INDEX},
                 <#noparse>${</#noparse>${GFX_DGTL_MTR_ID}<#noparse>}</#noparse>,      // digital meter ID
                 ${GFX_DGTL_MTR_LEFT},    // left
                 ${GFX_DGTL_MTR_TOP},     // top
                 ${GFX_DGTL_MTR_RIGHT},   // right
                 ${GFX_DGTL_MTR_BOTTOM},  // bottom             
                 ${GFX_DGTL_MTR_STATE},   // state
                 (uint32_t)${GFX_DGTL_MTR_VALUE},   // value
                 (uint16_t)${GFX_DGTL_MTR_NO_OF_DIGITS}, // no. of digits
                 (uint16_t)${GFX_DGTL_MTR_DOT_POSITION},// dot position
                 ${GFX_DGTL_MTR_ALIGNMENT},//alignment
                 ${GFX_DGTL_MTR_SCHEME}	//scheme
                 ); // use alternate scheme
        break;
</#macro>

<#macro GFX_HGC_CREATE_CHECKBOX INDEX GFX_INDEX GFX_CHECKBOX_ID GFX_CHECKBOX_LEFT GFX_CHECKBOX_TOP GFX_CHECKBOX_RIGHT GFX_CHECKBOX_BOTTOM GFX_CHECKBOX_TEXT GFX_CHECKBOX_STATE GFX_CHECKBOX_ALIGNMENT GFX_CHECKBOX_SCHEME>
    case <#noparse>${</#noparse>${GFX_CHECKBOX_ID}<#noparse>}</#noparse>:
        hgcObj.p<#noparse>${</#noparse>${GFX_CHECKBOX_ID}<#noparse>}</#noparse>Obj = GFX_GOL_CheckBoxCreate
                (
                 ${GFX_INDEX},
                 <#noparse>${</#noparse>${GFX_CHECKBOX_ID}<#noparse>}</#noparse>,      // Check Box ID
                 ${GFX_CHECKBOX_LEFT},    // left
                 ${GFX_CHECKBOX_TOP},     // top
                 ${GFX_CHECKBOX_RIGHT},   // right
                 ${GFX_CHECKBOX_BOTTOM},  // bottom 
                 ${GFX_CHECKBOX_STATE},   // state
                 (GFX_XCHAR*)checkBoxStr_${INDEX},			 		 
                 ${GFX_CHECKBOX_ALIGNMENT},//alignment
                 ${GFX_CHECKBOX_SCHEME}	//scheme
                 ); // use alternate scheme
        break;
</#macro>

<#macro GFX_HGC_CHECKBOX_TEXT_INIT INDEX TEXT>
static const GFX_XCHAR checkBoxStr_${INDEX}[] = { <#noparse>${</#noparse>${TEXT}<#noparse>}</#noparse> }; // <#noparse>${CONFIG_HGC_CHECKBOX_TEXT_STRING_</#noparse>${INDEX}<#noparse>}</#noparse>
</#macro>

<#macro GFX_HGC_CREATE_RADIOBUTTON INDEX GFX_INDEX GFX_RADIOBUTTON_ID GFX_RADIOBUTTON_LEFT GFX_RADIOBUTTON_TOP GFX_RADIOBUTTON_RIGHT GFX_RADIOBUTTON_BOTTOM GFX_RADIOBUTTON_TEXT GFX_RADIOBUTTON_STATE GFX_RADIOBUTTON_ALIGNMENT GFX_RADIOBUTTON_SCHEME GFX_RADIOBUTTON_GROUPNO GFX_RADIOBUTTON_NUM_GROUPS_ON_SCREEN>
    case <#noparse>${</#noparse>${GFX_RADIOBUTTON_ID}<#noparse>}</#noparse>:
        hgcObj.p<#noparse>${</#noparse>${GFX_RADIOBUTTON_ID}<#noparse>}</#noparse>Obj = GFX_GOL_RadioButtonListCreate
                (
                 ${GFX_INDEX},
                 <#noparse>${</#noparse>${GFX_RADIOBUTTON_ID}<#noparse>}</#noparse>,      // Radio button Box ID
                 ${GFX_RADIOBUTTON_LEFT},    // left
                 ${GFX_RADIOBUTTON_TOP},     // top
                 ${GFX_RADIOBUTTON_RIGHT},   // right
                 ${GFX_RADIOBUTTON_BOTTOM},  // bottom 
                 ${GFX_RADIOBUTTON_STATE},   // state
                 (GFX_XCHAR*)radioButtonStr_${INDEX},			 		 
                 ${GFX_RADIOBUTTON_ALIGNMENT},//alignment
                 ${GFX_RADIOBUTTON_SCHEME},	  //scheme
                 ${GFX_RADIOBUTTON_GROUPNO},  //group number
                 ${GFX_RADIOBUTTON_NUM_GROUPS_ON_SCREEN} //number of groups on screen
                 ); // use alternate scheme
        break;
</#macro>

<#macro GFX_HGC_RADIOBUTTON_TEXT_INIT INDEX TEXT>
static const GFX_XCHAR radioButtonStr_${INDEX}[] = { <#noparse>${</#noparse>${TEXT}<#noparse>}</#noparse> }; // <#noparse>${CONFIG_HGC_RADIOBUTTON_TEXT_STRING_</#noparse>${INDEX}<#noparse>}</#noparse>
</#macro>

<#macro GFX_HGC_CREATE_SCROLLBAR GFX_INDEX GFX_SCROLLBAR_ID GFX_SCROLLBAR_LEFT GFX_SCROLLBAR_TOP GFX_SCROLLBAR_RIGHT GFX_SCROLLBAR_BOTTOM GFX_SCROLLBAR_STATE GFX_SCROLLBAR_RANGE GFX_SCROLLBAR_PAGE GFX_SCROLLBAR_POS GFX_SCROLLBAR_SCHEME>
    case <#noparse>${</#noparse>${GFX_SCROLLBAR_ID}<#noparse>}</#noparse>:
        hgcObj.p<#noparse>${</#noparse>${GFX_SCROLLBAR_ID}<#noparse>}</#noparse>Obj = GFX_GOL_ScrollBarCreate
                (
                 ${GFX_INDEX},
                 <#noparse>${</#noparse>${GFX_SCROLLBAR_ID}<#noparse>}</#noparse>,           // Check Box ID
                 ${GFX_SCROLLBAR_LEFT},        // left
                 ${GFX_SCROLLBAR_TOP},        // top
                 ${GFX_SCROLLBAR_RIGHT},     // right
                 ${GFX_SCROLLBAR_BOTTOM},   // bottom 				 
                 ${GFX_SCROLLBAR_STATE},   //State
                 ${GFX_SCROLLBAR_RANGE},  // range
                 ${GFX_SCROLLBAR_PAGE},  // page 
                 ${GFX_SCROLLBAR_POS},  // pos 
                 ${GFX_SCROLLBAR_SCHEME}	//scheme
                 ); // use alternate scheme
        break;
</#macro>

<#macro GFX_HGC_CREATE_EDITBOX INDEX GFX_INDEX GFX_EDITBOX_ID GFX_EDITBOX_LEFT GFX_EDITBOX_TOP GFX_EDITBOX_RIGHT GFX_EDITBOX_BOTTOM GFX_EDITBOX_STATE GFX_EDITBOX_TEXT GFX_EDITBOX_NOOFCHARS GFX_EDITBOX_ALIGNMENT GFX_EDITBOX_SCHEME>
    case <#noparse>${</#noparse>${GFX_EDITBOX_ID}<#noparse>}</#noparse>:
        hgcObj.p<#noparse>${</#noparse>${GFX_EDITBOX_ID}<#noparse>}</#noparse>Obj = GFX_GOL_EditBoxCreate
                (
                 ${GFX_INDEX},
                 <#noparse>${</#noparse>${GFX_EDITBOX_ID}<#noparse>}</#noparse>,      // button ID
                 ${GFX_EDITBOX_LEFT},    // left
                 ${GFX_EDITBOX_TOP},     // top
                 ${GFX_EDITBOX_RIGHT},   // right
                 ${GFX_EDITBOX_BOTTOM},  // bottom
				 ${GFX_EDITBOX_STATE},   // state
				 (GFX_XCHAR*)editBoxStr_${INDEX},    // text
                 ${GFX_EDITBOX_NOOFCHARS},   // no. of chars
                 ${GFX_EDITBOX_ALIGNMENT},       //alignment
                 ${GFX_EDITBOX_SCHEME}
                 ); // use alternate scheme
        break;
</#macro>

<#macro GFX_HGC_EDITBOX_TEXT_INIT INDEX TEXT>
static const GFX_XCHAR editBoxStr_${INDEX}[] = { <#noparse>${</#noparse>${TEXT}<#noparse>}</#noparse> }; // <#noparse>${CONFIG_HGC_EDITBOX_TEXT_STRING_</#noparse>${INDEX}<#noparse>}</#noparse>
</#macro>

<#macro GFX_HGC_CREATE_STATICTEXT INDEX GFX_INDEX GFX_STATICTEXT_ID GFX_STATICTEXT_LEFT GFX_STATICTEXT_TOP GFX_STATICTEXT_RIGHT GFX_STATICTEXT_BOTTOM GFX_STATICTEXT_STATE GFX_STATICTEXT_TEXT GFX_STATICTEXT_FRAME  GFX_STATICTEXT_ALIGNMENT GFX_STATICTEXT_SCHEME>
    case <#noparse>${</#noparse>${GFX_STATICTEXT_ID}<#noparse>}</#noparse>:
        hgcObj.p<#noparse>${</#noparse>${GFX_STATICTEXT_ID}<#noparse>}</#noparse>Obj = GFX_GOL_StaticTextCreate
                (
                 ${GFX_INDEX},
                 <#noparse>${</#noparse>${GFX_STATICTEXT_ID}<#noparse>}</#noparse>,      // button ID
                 ${GFX_STATICTEXT_LEFT},    // left
                 ${GFX_STATICTEXT_TOP},     // top
                 ${GFX_STATICTEXT_RIGHT},   // right
                 ${GFX_STATICTEXT_BOTTOM},  // bottom
                 ${GFX_STATICTEXT_STATE},   // state
                 (GFX_XCHAR*)staticTextStr_${INDEX},    // text
                 ${GFX_STATICTEXT_ALIGNMENT},       //alignment
                 ${GFX_STATICTEXT_SCHEME}
                 ); // use alternate scheme
        break;
</#macro>

<#macro GFX_HGC_STATIC_TEXT_INIT INDEX TEXT>
static const GFX_XCHAR staticTextStr_${INDEX}[] = { <#noparse>${</#noparse>${TEXT}<#noparse>}</#noparse> }; // <#noparse>${CONFIG_HGC_STATICTEXT_TEXT_STRING_</#noparse>${INDEX}<#noparse>}</#noparse>
</#macro>

<#macro GFX_HGC_CREATE_WINDOW INDEX GFX_INDEX GFX_WINDOW_ID GFX_WINDOW_LEFT GFX_WINDOW_TOP GFX_WINDOW_RIGHT GFX_WINDOW_BOTTOM GFX_WINDOW_STATE GFX_WINDOW_IMAGE GFX_WINDOW_TEXT GFX_WINDOW_ALIGNMENT GFX_WINDOW_SCHEME>
    case <#noparse>${</#noparse>${GFX_WINDOW_ID}<#noparse>}</#noparse>:
        hgcObj.p<#noparse>${</#noparse>${GFX_WINDOW_ID}<#noparse>}</#noparse>Obj = GFX_GOL_WindowCreate
                (
                 ${GFX_INDEX},
                 <#noparse>${</#noparse>${GFX_WINDOW_ID}<#noparse>}</#noparse>,      // button ID
                 ${GFX_WINDOW_LEFT},    // left
                 ${GFX_WINDOW_TOP},     // top
                 ${GFX_WINDOW_RIGHT},   // right				 
                 ${GFX_WINDOW_BOTTOM},  // bottom
                 ${GFX_WINDOW_STATE},   // state
                 ${GFX_WINDOW_IMAGE},     // press image                 
                 (GFX_XCHAR*)windowTextStr_${INDEX},    // text
                 ${GFX_WINDOW_ALIGNMENT},       //alignment
                 ${GFX_WINDOW_SCHEME}
                 ); // use alternate scheme
        break;
</#macro>

<#macro GFX_HGC_WINDOW_TEXT_INIT INDEX TEXT>
static const GFX_XCHAR windowTextStr_${INDEX}[] = { <#noparse>${</#noparse>${TEXT}<#noparse>}</#noparse> }; // <#noparse>${CONFIG_HGC_WINDOW_TEXT_STRING_</#noparse>${INDEX}<#noparse>}</#noparse>
</#macro>

<#macro GFX_HGC_CREATE_PICTURE INDEX GFX_INDEX GFX_PICTURE_ID GFX_PICTURE_LEFT GFX_PICTURE_TOP GFX_PICTURE_RIGHT GFX_PICTURE_BOTTOM GFX_PICTURE_STATE GFX_PICTURE_IMAGE GFX_PICTURE_SCALE GFX_PICTURE_SCHEME>
    case <#noparse>${</#noparse>${GFX_PICTURE_ID}<#noparse>}</#noparse>:
        hgcObj.p<#noparse>${</#noparse>${GFX_PICTURE_ID}<#noparse>}</#noparse>Obj = GFX_GOL_PictureControlCreate
                (
                 ${GFX_INDEX},
                 <#noparse>${</#noparse>${GFX_PICTURE_ID}<#noparse>}</#noparse>,      // picture ID
                 ${GFX_PICTURE_LEFT},    // left
                 ${GFX_PICTURE_TOP},     // top
                 ${GFX_PICTURE_RIGHT},   // right				 
                 ${GFX_PICTURE_BOTTOM},  // bottom
				 ${GFX_PICTURE_STATE},   // state                 
                 ${GFX_PICTURE_SCALE},     // scale
                 <#noparse>${</#noparse>${GFX_PICTURE_IMAGE}<#noparse>}</#noparse>,    // bitmap
                 ${GFX_PICTURE_SCHEME}
                 );
        break;
</#macro>

<#macro GFX_HGC_CREATE_PROGRESSBAR
			GFX_INDEX 
			GFX_PROGRESSBAR_ID
			GFX_PROGRESSBAR_LEFT
			GFX_PROGRESSBAR_TOP
			GFX_PROGRESSBAR_RIGHT
			GFX_PROGRESSBAR_BOTTOM
			GFX_PROGRESSBAR_STATE
			GFX_PROGRESSBAR_POS
			GFX_PROGRESSBAR_RANGE
			GFX_PROGRESSBAR_SCHEME>
    case <#noparse>${</#noparse>${GFX_PROGRESSBAR_ID}<#noparse>}</#noparse>:
        hgcObj.p<#noparse>${</#noparse>${GFX_PROGRESSBAR_ID}<#noparse>}</#noparse>Obj = GFX_GOL_ProgressBarCreate
                (
                 ${GFX_INDEX},
                 <#noparse>${</#noparse>${GFX_PROGRESSBAR_ID}<#noparse>}</#noparse>,      // progressbar ID
                 ${GFX_PROGRESSBAR_LEFT},    // left
                 ${GFX_PROGRESSBAR_TOP},     // top
                 ${GFX_PROGRESSBAR_RIGHT},   // right				 
                 ${GFX_PROGRESSBAR_BOTTOM},  // bottom
				 ${GFX_PROGRESSBAR_STATE},   // state
				 ${GFX_PROGRESSBAR_POS},     //position                 
                 ${GFX_PROGRESSBAR_RANGE},   // range				 
                 ${GFX_PROGRESSBAR_SCHEME}
                 );
        GFX_GOL_ProgressBarPositionSet(hgcObj.p<#noparse>${</#noparse>${GFX_PROGRESSBAR_ID}<#noparse>}</#noparse>Obj, ${GFX_PROGRESSBAR_POS});
        break;
</#macro>

<#macro GFX_HGC_CREATE_METER
            INDEX
			GFX_INDEX 
			GFX_METER_ID
			GFX_METER_LEFT
			GFX_METER_TOP
			GFX_METER_RIGHT
			GFX_METER_BOTTOM
			GFX_METER_STATE
			GFX_METER_VALUE
			GFX_METER_MIN_VALUE
			GFX_METER_MAX_VALUE
			GFX_METER_TYPE
			GFX_METER_TITLE_FONT
			GFX_METER_VALUE_FONT
			GFX_METER_SCHEME
            GFX_METER_COLOR1
            GFX_METER_COLOR2
            GFX_METER_COLOR3
            GFX_METER_COLOR4
            GFX_METER_COLOR5
            GFX_METER_COLOR6>
    case <#noparse>${</#noparse>${GFX_METER_ID}<#noparse>}</#noparse>:
        hgcObj.p<#noparse>${</#noparse>${GFX_METER_ID}<#noparse>}</#noparse>Obj = GFX_GOL_MeterCreate
                (
                 ${GFX_INDEX},
                 <#noparse>${</#noparse>${GFX_METER_ID}<#noparse>}</#noparse>,      // meter ID
                 ${GFX_METER_LEFT},    // left
                 ${GFX_METER_TOP},     // top
                 ${GFX_METER_RIGHT},   // right				 
                 ${GFX_METER_BOTTOM},  // bottom
				 ${GFX_METER_STATE},   // state
                 ${GFX_METER_TYPE}, // type
				 ${GFX_METER_VALUE},     //value                 
                 ${GFX_METER_MIN_VALUE},   // min value
                 ${GFX_METER_MAX_VALUE},   // max value
                 (GFX_RESOURCE_HDR*) <#noparse>${</#noparse>${GFX_METER_TITLE_FONT}<#noparse>}</#noparse>,   // title font
                 (GFX_RESOURCE_HDR*) <#noparse>${</#noparse>${GFX_METER_VALUE_FONT}<#noparse>}</#noparse>,   // value font
                 (GFX_XCHAR*)meterStr_${INDEX},    // text
                 ${GFX_METER_SCHEME}
                 );
<#noparse><#if CONFIG_HGC_METER_USE_COLORS_</#noparse>${INDEX}<#noparse> = true></#noparse>
<#noparse>        GFX_GOL_MeterScaleColorsSet(hgcObj.p</#noparse><#noparse>${</#noparse>${GFX_METER_ID}<#noparse>}</#noparse><#noparse>Obj,</#noparse> 
<#noparse>                        GFX_RGBConvert(</#noparse>${GFX_METER_COLOR1}<#noparse>),</#noparse>
<#noparse>                        GFX_RGBConvert(</#noparse>${GFX_METER_COLOR2}<#noparse>),</#noparse>
<#noparse>                        GFX_RGBConvert(</#noparse>${GFX_METER_COLOR3}<#noparse>),</#noparse>
<#noparse>                        GFX_RGBConvert(</#noparse>${GFX_METER_COLOR4}<#noparse>),</#noparse>
<#noparse>                        GFX_RGBConvert(</#noparse>${GFX_METER_COLOR5}<#noparse>),</#noparse>
<#noparse>                        GFX_RGBConvert(</#noparse>${GFX_METER_COLOR6}<#noparse>));</#noparse>
<#noparse></#if></#noparse>
        break;
</#macro>

<#macro GFX_HGC_CREATE_LINE INDEX GFX_INDEX GFX_LINE_ID HGC_LINE_P1X HGC_LINE_P1Y HGC_LINE_P2X HGC_LINE_P2Y GFX_LINE_STYLE HGC_LINE_RED HGC_LINE_GREEN HGC_LINE_BLUE>
		case <#noparse>${</#noparse>${GFX_LINE_ID}<#noparse>}</#noparse>:
		{
			GFX_ColorSet(${GFX_INDEX}, GFX_RGBConvert(<#noparse>${</#noparse>${HGC_LINE_RED}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_LINE_GREEN}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_LINE_BLUE}<#noparse>}</#noparse>));
			GFX_LineStyleSet(${GFX_INDEX}, <#noparse>${</#noparse>${GFX_LINE_STYLE}<#noparse>}</#noparse>);
			GFX_LineDraw(${GFX_INDEX},
						 <#noparse>${</#noparse>${HGC_LINE_P1X}<#noparse>}</#noparse>,  // p1x
						 <#noparse>${</#noparse>${HGC_LINE_P1Y}<#noparse>}</#noparse>,  // p1y
						 <#noparse>${</#noparse>${HGC_LINE_P2X}<#noparse>}</#noparse>,  // p2x
						 <#noparse>${</#noparse>${HGC_LINE_P2Y}<#noparse>}</#noparse>); // p2y
			break;
		}		
</#macro>

<#macro GFX_HGC_CREATE_RECTANGLE
			INDEX
			GFX_INDEX
			GFX_RECTANGLE_ID
			HGC_RECTANGLE_P1X
			HGC_RECTANGLE_P1Y
			HGC_RECTANGLE_P2X
			HGC_RECTANGLE_P2Y
			HGC_RECTANGLE_RADIUS
			HGC_RECTANGLE_OUTLINE
			HGC_RECTANGLE_OUTLINE_STYLE
			HGC_RECTANGLE_OUTLINE_RED
			HGC_RECTANGLE_OUTLINE_GREEN
			HGC_RECTANGLE_OUTLINE_BLUE
			HGC_RECTANGLE_FILL_STYLE
			HGC_RECTANGLE_FILL_RED
			HGC_RECTANGLE_FILL_GREEN
			HGC_RECTANGLE_FILL_BLUE
			HGC_RECTANGLE_ALPHA
			HGC_RECTANGLE_START_RED
			HGC_RECTANGLE_START_GREEN
			HGC_RECTANGLE_START_BLUE
			HGC_RECTANGLE_END_RED
			HGC_RECTANGLE_END_GREEN
			HGC_RECTANGLE_END_BLUE
			>
		case <#noparse>${</#noparse>${GFX_RECTANGLE_ID}<#noparse>}</#noparse>:
		{
			<#noparse><#if </#noparse>${HGC_RECTANGLE_FILL_STYLE}<#noparse>??></#noparse>	
			<#noparse><#if </#noparse>${HGC_RECTANGLE_FILL_STYLE}<#noparse> == "GFX_FILL_STYLE_COLOR"></#noparse>
			GFX_FillStyleSet(${GFX_INDEX}, GFX_FILL_STYLE_COLOR);
			GFX_ColorSet(${GFX_INDEX}, GFX_RGBConvert(<#noparse>${</#noparse>${HGC_RECTANGLE_FILL_RED}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_RECTANGLE_FILL_GREEN}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_RECTANGLE_FILL_BLUE}<#noparse>}</#noparse>));
			<#noparse><#elseif </#noparse>${HGC_RECTANGLE_FILL_STYLE}<#noparse> == "GFX_FILL_STYLE_ALPHA_COLOR"></#noparse>
			GFX_FillStyleSet(${GFX_INDEX}, GFX_FILL_STYLE_ALPHA_COLOR);
			GFX_ColorSet(${GFX_INDEX}, GFX_RGBConvert(<#noparse>${</#noparse>${HGC_RECTANGLE_FILL_RED}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_RECTANGLE_FILL_GREEN}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_RECTANGLE_FILL_BLUE}<#noparse>}</#noparse>));
			GFX_AlphaBlendingValueSet(${GFX_INDEX}, <#noparse>${</#noparse>${HGC_RECTANGLE_ALPHA}<#noparse>}</#noparse>);
			<#noparse><#else></#noparse>
			GFX_FillStyleSet(${GFX_INDEX}, <#noparse>${</#noparse>${HGC_RECTANGLE_FILL_STYLE}<#noparse>}</#noparse>);
			GFX_GradientColorSet(${GFX_INDEX},
			                    GFX_RGBConvert(<#noparse>${</#noparse>${HGC_RECTANGLE_START_RED}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_RECTANGLE_START_GREEN}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_RECTANGLE_START_BLUE}<#noparse>}</#noparse>),
			                    GFX_RGBConvert(<#noparse>${</#noparse>${HGC_RECTANGLE_END_RED}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_RECTANGLE_END_GREEN}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_RECTANGLE_END_BLUE}<#noparse>}</#noparse>));	
			<#noparse></#if></#noparse>
			<#noparse><#if </#noparse>${HGC_RECTANGLE_RADIUS}<#noparse>??</#noparse>>
			GFX_RectangleRoundFillDraw(${GFX_INDEX},
									   <#noparse>${</#noparse>${HGC_RECTANGLE_P1X}<#noparse>}</#noparse>, // p1x
									   <#noparse>${</#noparse>${HGC_RECTANGLE_P1Y}<#noparse>}</#noparse>, // p1y
									   <#noparse>${</#noparse>${HGC_RECTANGLE_P2X}<#noparse>}</#noparse>, // p2x
									   <#noparse>${</#noparse>${HGC_RECTANGLE_P2Y}<#noparse>}</#noparse>, // p2y
									   <#noparse>${</#noparse>${HGC_RECTANGLE_RADIUS}<#noparse>}</#noparse>); // radius
			<#noparse><#else></#noparse>
			GFX_RectangleFillDraw(${GFX_INDEX},
								  <#noparse>${</#noparse>${HGC_RECTANGLE_P1X}<#noparse>}</#noparse>,  // p1x
								  <#noparse>${</#noparse>${HGC_RECTANGLE_P1Y}<#noparse>}</#noparse>,  // p1y
								  <#noparse>${</#noparse>${HGC_RECTANGLE_P2X}<#noparse>}</#noparse>,  // p2x
								  <#noparse>${</#noparse>${HGC_RECTANGLE_P2Y}<#noparse>}</#noparse>); // p2y
			<#noparse></#if></#noparse>
			
			<#noparse></#if></#noparse>
			<#noparse><#if </#noparse>${HGC_RECTANGLE_OUTLINE}<#noparse>??></#noparse>
			GFX_ColorSet(${GFX_INDEX}, GFX_RGBConvert(<#noparse>${</#noparse>${HGC_RECTANGLE_OUTLINE_RED}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_RECTANGLE_OUTLINE_GREEN}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_RECTANGLE_OUTLINE_BLUE}<#noparse>}</#noparse>));
			GFX_LineStyleSet(${GFX_INDEX}, <#noparse>${</#noparse>${HGC_RECTANGLE_OUTLINE_STYLE}<#noparse>}</#noparse>);
			<#noparse><#if </#noparse>${HGC_RECTANGLE_RADIUS}<#noparse>??</#noparse>>
			GFX_RectangleRoundDraw(${GFX_INDEX},
								   <#noparse>${</#noparse>${HGC_RECTANGLE_P1X}<#noparse>}</#noparse>, // p1x
								   <#noparse>${</#noparse>${HGC_RECTANGLE_P1Y}<#noparse>}</#noparse>, // p1y
								   <#noparse>${</#noparse>${HGC_RECTANGLE_P2X}<#noparse>}</#noparse>, // p2x
								   <#noparse>${</#noparse>${HGC_RECTANGLE_P2Y}<#noparse>}</#noparse>, // p2y
								   <#noparse>${</#noparse>${HGC_RECTANGLE_RADIUS}<#noparse>}</#noparse>); // radius
			<#noparse><#else></#noparse>
			GFX_RectangleDraw(${GFX_INDEX},
							  <#noparse>${</#noparse>${HGC_RECTANGLE_P1X}<#noparse>}</#noparse>,  // p1x
							  <#noparse>${</#noparse>${HGC_RECTANGLE_P1Y}<#noparse>}</#noparse>,  // p1y
							  <#noparse>${</#noparse>${HGC_RECTANGLE_P2X}<#noparse>}</#noparse>,  // p2x
							  <#noparse>${</#noparse>${HGC_RECTANGLE_P2Y}<#noparse>}</#noparse>); // p2y
			<#noparse></#if></#noparse>
			
			<#noparse></#if></#noparse>
			break;
		}	
</#macro>

<#macro GFX_HGC_CREATE_CIRCLE
			INDEX
			GFX_INDEX
			GFX_CIRCLE_ID
			HGC_CIRCLE_ORIGIN_X
			HGC_CIRCLE_ORIGIN_Y
			HGC_CIRCLE_RADIUS
			HGC_CIRCLE_OUTLINE
			HGC_CIRCLE_OUTLINE_STYLE
			HGC_CIRCLE_OUTLINE_RED
			HGC_CIRCLE_OUTLINE_GREEN
			HGC_CIRCLE_OUTLINE_BLUE
			HGC_CIRCLE_FILL_STYLE
			HGC_CIRCLE_FILL_RED
			HGC_CIRCLE_FILL_GREEN
			HGC_CIRCLE_FILL_BLUE
			HGC_CIRCLE_ALPHA
			HGC_CIRCLE_START_RED
			HGC_CIRCLE_START_GREEN
			HGC_CIRCLE_START_BLUE
			HGC_CIRCLE_END_RED
			HGC_CIRCLE_END_GREEN
			HGC_CIRCLE_END_BLUE
			>
		case <#noparse>${</#noparse>${GFX_CIRCLE_ID}<#noparse>}</#noparse>:
		{
			<#noparse><#if </#noparse>${HGC_CIRCLE_FILL_STYLE}<#noparse>??></#noparse>	
			<#noparse><#if </#noparse>${HGC_CIRCLE_FILL_STYLE}<#noparse> == "GFX_FILL_STYLE_COLOR"></#noparse>
			GFX_FillStyleSet(${GFX_INDEX}, GFX_FILL_STYLE_COLOR);
			GFX_ColorSet(${GFX_INDEX}, GFX_RGBConvert(<#noparse>${</#noparse>${HGC_CIRCLE_FILL_RED}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_CIRCLE_FILL_GREEN}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_CIRCLE_FILL_BLUE}<#noparse>}</#noparse>));
			<#noparse><#elseif </#noparse>${HGC_CIRCLE_FILL_STYLE}<#noparse> == "GFX_FILL_STYLE_ALPHA_COLOR"></#noparse>
			GFX_FillStyleSet(${GFX_INDEX}, GFX_FILL_STYLE_ALPHA_COLOR);
			GFX_ColorSet(${GFX_INDEX}, GFX_RGBConvert(<#noparse>${</#noparse>${HGC_CIRCLE_FILL_RED}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_CIRCLE_FILL_GREEN}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_CIRCLE_FILL_BLUE}<#noparse>}</#noparse>));
			GFX_AlphaBlendingValueSet(${GFX_INDEX}, <#noparse>${</#noparse>${HGC_CIRCLE_ALPHA}<#noparse>}</#noparse>);
			<#noparse><#else></#noparse>
			GFX_FillStyleSet(${GFX_INDEX}, <#noparse>${</#noparse>${HGC_CIRCLE_FILL_STYLE}<#noparse>}</#noparse>);
			GFX_GradientColorSet(${GFX_INDEX},
			                     GFX_RGBConvert(<#noparse>${</#noparse>${HGC_CIRCLE_START_RED}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_CIRCLE_START_GREEN}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_CIRCLE_START_BLUE}<#noparse>}</#noparse>),
			                     GFX_RGBConvert(<#noparse>${</#noparse>${HGC_CIRCLE_END_RED}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_CIRCLE_END_GREEN}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_CIRCLE_END_BLUE}<#noparse>}</#noparse>));	
			<#noparse></#if></#noparse>
			GFX_CircleFillDraw(${GFX_INDEX},
							   <#noparse>${</#noparse>${HGC_CIRCLE_ORIGIN_X}<#noparse>}</#noparse>, // p1x
							   <#noparse>${</#noparse>${HGC_CIRCLE_ORIGIN_Y}<#noparse>}</#noparse>, // p1y
							   <#noparse>${</#noparse>${HGC_CIRCLE_RADIUS}<#noparse>}</#noparse>); // radius
						
			<#noparse></#if></#noparse>
			<#noparse><#if </#noparse>${HGC_CIRCLE_OUTLINE}<#noparse>??></#noparse>
			GFX_ColorSet(${GFX_INDEX},GFX_RGBConvert(<#noparse>${</#noparse>${HGC_CIRCLE_OUTLINE_RED}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_CIRCLE_OUTLINE_GREEN}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_CIRCLE_OUTLINE_BLUE}<#noparse>}</#noparse>));
			GFX_LineStyleSet(${GFX_INDEX}, <#noparse>${</#noparse>${HGC_CIRCLE_OUTLINE_STYLE}<#noparse>}</#noparse>);
			GFX_CircleDraw(${GFX_INDEX},
						   <#noparse>${</#noparse>${HGC_CIRCLE_ORIGIN_X}<#noparse>}</#noparse>, // p1x
						   <#noparse>${</#noparse>${HGC_CIRCLE_ORIGIN_Y}<#noparse>}</#noparse>, // p1y
						   <#noparse>${</#noparse>${HGC_CIRCLE_RADIUS}<#noparse>}</#noparse>); // radius
						   
			<#noparse></#if></#noparse>
			break;
		}	
</#macro>

<#macro GFX_HGC_CREATE_IMAGE
			INDEX
			GFX_INDEX
			GFX_IMAGE_ID
			HGC_IMAGE_ORIGIN_X
			HGC_IMAGE_ORIGIN_Y
			HGC_IMAGE_IMAGE_ID
			HGC_IMAGE_TRANSPARENCY_RED
			HGC_IMAGE_TRANSPARENCY_GREEN
			HGC_IMAGE_TRANSPARENCY_BLUE
			HGC_IMAGE_CLIP_X
			HGC_IMAGE_CLIP_Y
			HGC_IMAGE_CLIP_WIDTH
			HGC_IMAGE_CLIP_HEIGHT
			>
		case <#noparse>${</#noparse>${GFX_IMAGE_ID}<#noparse>}</#noparse>:
		{
			<#noparse><#if </#noparse>${HGC_IMAGE_TRANSPARENCY_RED}<#noparse>??></#noparse>
			GFX_TransparentColorEnable(${GFX_INDEX}, GFX_RGBConvert(<#noparse>${</#noparse>${HGC_IMAGE_TRANSPARENCY_RED}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_IMAGE_TRANSPARENCY_GREEN}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_IMAGE_TRANSPARENCY_BLUE}<#noparse>}</#noparse>)); // enable transparency
			<#noparse></#if></#noparse>
			<#noparse><#if </#noparse>${HGC_IMAGE_CLIP_X}<#noparse>??></#noparse>
			GFX_ImagePartialDraw(${GFX_INDEX},
			                     <#noparse>${</#noparse>${HGC_IMAGE_ORIGIN_X}<#noparse>}</#noparse>, // draw point x
						         <#noparse>${</#noparse>${HGC_IMAGE_ORIGIN_Y}<#noparse>}</#noparse>, // draw point y
						         <#noparse>${</#noparse>${HGC_IMAGE_CLIP_X}<#noparse>}</#noparse>, // clip offset x
						         <#noparse>${</#noparse>${HGC_IMAGE_CLIP_Y}<#noparse>}</#noparse>, // clip offset y
						         <#noparse>${</#noparse>${HGC_IMAGE_CLIP_WIDTH}<#noparse>}</#noparse>, // clip width
						         <#noparse>${</#noparse>${HGC_IMAGE_CLIP_HEIGHT}<#noparse>}</#noparse>, // clip height
						         (GFX_RESOURCE_HDR*)&<#noparse>${</#noparse>${HGC_IMAGE_IMAGE_ID}<#noparse>}</#noparse>); // image
			<#noparse><#else></#noparse>
			GFX_ImageDraw(${GFX_INDEX},
			              <#noparse>${</#noparse>${HGC_IMAGE_ORIGIN_X}<#noparse>}</#noparse>, // draw point x
						  <#noparse>${</#noparse>${HGC_IMAGE_ORIGIN_Y}<#noparse>}</#noparse>, // draw point y
						  (GFX_RESOURCE_HDR*)&<#noparse>${</#noparse>${HGC_IMAGE_IMAGE_ID}<#noparse>}</#noparse>); // image
			<#noparse></#if></#noparse>
			<#noparse><#if </#noparse>${HGC_IMAGE_TRANSPARENCY_RED}<#noparse>??></#noparse>
			GFX_TransparentColorDisable(GFX_INDEX_0); // disable transparency
			<#noparse></#if></#noparse>
			break;
		}	
</#macro>

<#macro GFX_HGC_CREATE_TEXT
			INDEX
			GFX_INDEX
			GFX_TEXT_ID
			HGC_TEXT_ORIGIN_X
			HGC_TEXT_ORIGIN_Y
			HGC_TEXT_STRING
			HGC_TEXT_FONT_ID
			HGC_TEXT_COLOR_RED
			HGC_TEXT_COLOR_GREEN
			HGC_TEXT_COLOR_BLUE
			HGC_TEXT_CLIP_X
			HGC_TEXT_CLIP_Y
			HGC_TEXT_ALIGNMENT
			>
		case <#noparse>${</#noparse>${GFX_TEXT_ID}<#noparse>}</#noparse>:
		{
			char <#noparse>${</#noparse>${GFX_TEXT_ID}<#noparse>}</#noparse>_text[] = "<#noparse>${</#noparse>${HGC_TEXT_STRING}<#noparse>}</#noparse>";
			
			GFX_ColorSet(${GFX_INDEX}, GFX_RGBConvert(<#noparse>${</#noparse>${HGC_TEXT_COLOR_RED}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_TEXT_COLOR_GREEN}<#noparse>}</#noparse>, <#noparse>${</#noparse>${HGC_TEXT_COLOR_BLUE}<#noparse>}</#noparse>)); // set color
			GFX_FontSet(${GFX_INDEX}, (GFX_RESOURCE_HDR*)&<#noparse>${</#noparse>${HGC_TEXT_FONT_ID}<#noparse>}</#noparse>); // set font
			<#noparse><#if </#noparse>${HGC_TEXT_CLIP_X}<#noparse>??></#noparse>
			GFX_TextStringBoxDraw(${GFX_INDEX},
			                      <#noparse>${</#noparse>${HGC_TEXT_ORIGIN_X}<#noparse>}</#noparse>, // draw point x
						          <#noparse>${</#noparse>${HGC_TEXT_ORIGIN_Y}<#noparse>}</#noparse>, // draw point y
						          <#noparse>${</#noparse>${HGC_TEXT_CLIP_X}<#noparse>}</#noparse>, // clip area bottom right point x
						          <#noparse>${</#noparse>${HGC_TEXT_CLIP_Y}<#noparse>}</#noparse>, // clip area bottom right point y
								  (char*)&<#noparse>${</#noparse>${GFX_TEXT_ID}<#noparse>}</#noparse>_text, // string
								  0, // length
								  <#noparse>${</#noparse>${HGC_TEXT_ALIGNMENT}<#noparse>}</#noparse>); // alignment
			<#noparse><#else></#noparse>
			GFX_TextStringDraw(${GFX_INDEX},
			                   <#noparse>${</#noparse>${HGC_TEXT_ORIGIN_X}<#noparse>}</#noparse>, // draw point x
						       <#noparse>${</#noparse>${HGC_TEXT_ORIGIN_Y}<#noparse>}</#noparse>, // draw point y
                               (char*)&<#noparse>${</#noparse>${GFX_TEXT_ID}<#noparse>}</#noparse>_text, // string
							   0); // length
			<#noparse></#if></#noparse>
			break;
		}	
</#macro>

<#macro GFX_HGC_BUTTON_GENERATE_EVENTS
			GFX_BUTTON_ID
			GFX_INDEX
			GFX_BUTTON_INDEX
			GFX_BTN_PRESSED_EVENT_ACTION_COUNT
			GFX_BTN_STILLPRESSED_EVENT_ACTION_COUNT
			GFX_BTN_RELEASED_EVENT_ACTION_COUNT
			GFX_BTN_CANCELPRESS_EVENT_ACTION_COUNT>
        case <#noparse>${</#noparse>${GFX_BUTTON_ID}<#noparse>}</#noparse>:
			<#if GFX_BTN_PRESSED_EVENT_ACTION_COUNT?eval??>
			if (objMsg == GFX_GOL_BUTTON_ACTION_PRESSED)
            {
				// Button Pressed Event Code
				<#assign count="${GFX_BTN_PRESSED_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_BTN_${GFX_BUTTON_INDEX}_EVENT_PRESSED_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			<#if GFX_BTN_STILLPRESSED_EVENT_ACTION_COUNT?eval??>
            if (objMsg == GFX_GOL_BUTTON_ACTION_STILLPRESSED)
            {
                // Button Still Pressed Event Code
                <#assign count="${GFX_BTN_STILLPRESSED_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_BTN_${GFX_BUTTON_INDEX}_EVENT_STILLPRESSED_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			<#if GFX_BTN_RELEASED_EVENT_ACTION_COUNT?eval??>
            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                // Button Release Event Code
                <#assign count="${GFX_BTN_RELEASED_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_BTN_${GFX_BUTTON_INDEX}_EVENT_RELEASED_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			<#if GFX_BTN_CANCELPRESS_EVENT_ACTION_COUNT?eval??>
            if (objMsg == GFX_GOL_BUTTON_ACTION_CANCELPRESS)
            {
                // Button Cancel Press Event Code
                <#assign count="${GFX_BTN_CANCELPRESS_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_BTN_${GFX_BUTTON_INDEX}_EVENT_CANCELPRESS_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			
            return true;
</#macro>

<#macro GFX_HGC_DGTL_MTR_GENERATE_EVENTS
			GFX_DGTL_MTR_ID
			GFX_INDEX
			GFX_DGTL_MTR_INDEX
			GFX_DGTL_MTR_SELECTED_EVENT_ACTION_COUNT>
        case <#noparse>${</#noparse>${GFX_DGTL_MTR_ID}<#noparse>}</#noparse>:
			<#if GFX_DGTL_MTR_SELECTED_EVENT_ACTION_COUNT?eval??>
			if (objMsg == GFX_GOL_DIGITALMETER_ACTION_SELECTED)
            {
				// Digital Meter Selected Event Code
				<#assign count="${GFX_DGTL_MTR_SELECTED_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_DGTL_MTR_${GFX_DGTL_MTR_INDEX}_EVENT_SELECTED_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			
            return true;
</#macro>

<#macro GFX_HGC_CHECKBOX_GENERATE_EVENTS
			GFX_CHECKBOX_ID
			GFX_INDEX
			GFX_CHECKBOX_INDEX
			GFX_CHECKBOX_CHECKED_EVENT_ACTION_COUNT
			GFX_CHECKBOX_UNCHECKED_EVENT_ACTION_COUNT>
        case <#noparse>${</#noparse>${GFX_CHECKBOX_ID}<#noparse>}</#noparse>:
			<#if GFX_CHECKBOX_CHECKED_EVENT_ACTION_COUNT?eval??>
			if (objMsg == GFX_GOL_CHECKBOX_ACTION_CHECKED)
            {
				// Checkbox Check Event Code
				<#assign count="${GFX_CHECKBOX_CHECKED_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_CHECKBOX_${GFX_CHECKBOX_INDEX}_EVENT_CHECKED_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			<#if GFX_CHECKBOX_UNCHECKED_EVENT_ACTION_COUNT?eval??>
            if (objMsg == GFX_GOL_CHECKBOX_ACTION_UNCHECKED)
            {
                // Checkbox Uncheck Event Code
                <#assign count="${GFX_CHECKBOX_UNCHECKED_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_CHECKBOX_${GFX_CHECKBOX_INDEX}_EVENT_UNCHECKED_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			
            return true;
</#macro>

<#macro GFX_HGC_RADIOBUTTON_GENERATE_EVENTS
			GFX_RADIOBUTTON_ID
			GFX_INDEX
			GFX_RADIOBUTTON_INDEX
			GFX_RADIOBUTTON_CHECKED_EVENT_ACTION_COUNT>
        case <#noparse>${</#noparse>${GFX_RADIOBUTTON_ID}<#noparse>}</#noparse>:
			<#if GFX_RADIOBUTTON_CHECKED_EVENT_ACTION_COUNT?eval??>
			if (objMsg == GFX_GOL_RADIOBUTTON_ACTION_CHECKED)
            {
				// RadioButton Check Event Code
				<#assign count="${GFX_RADIOBUTTON_CHECKED_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_RADIOBUTTON_${GFX_RADIOBUTTON_INDEX}_EVENT_CHECKED_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			
            return true;
</#macro>

<#macro GFX_HGC_SCROLLBAR_GENERATE_EVENTS
			GFX_SCROLLBAR_ID
			GFX_INDEX
			GFX_SCROLLBAR_INDEX
			GFX_SCROLLBAR_INCREMENT_EVENT_ACTION_COUNT
			GFX_SCROLLBAR_DECREMENT_EVENT_ACTION_COUNT>
        case <#noparse>${</#noparse>${GFX_SCROLLBAR_ID}<#noparse>}</#noparse>:
			<#if GFX_SCROLLBAR_INCREMENT_EVENT_ACTION_COUNT?eval??>
			if (objMsg == GFX_GOL_SCROLLBAR_ACTION_INC)
            {
				// Scrollbar Increment Event Code
				<#assign count="${GFX_SCROLLBAR_INCREMENT_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_SCROLLBAR_${GFX_SCROLLBAR_INDEX}_EVENT_INCREMENT_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			<#if GFX_SCROLLBAR_DECREMENT_EVENT_ACTION_COUNT?eval??>
            if (objMsg == GFX_GOL_SCROLLBAR_ACTION_DEC)
            {
                // Scrollbar Decrement Event Code
                <#assign count="${GFX_SCROLLBAR_DECREMENT_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_SCROLLBAR_${GFX_SCROLLBAR_INDEX}_EVENT_DECREMENT_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			
            return true;
</#macro>

<#macro GFX_HGC_EDITBOX_GENERATE_EVENTS
			GFX_EDITBOX_ID
			GFX_INDEX
			GFX_EDITBOX_INDEX
			GFX_EDITBOX_ADD_CHAR_EVENT_ACTION_COUNT
			GFX_EDITBOX_DEL_CHAR_EVENT_ACTION_COUNT
			GFX_EDITBOX_TOUCHSCREEN_EVENT_ACTION_COUNT>
        case <#noparse>${</#noparse>${GFX_EDITBOX_ID}<#noparse>}</#noparse>:
			<#if GFX_EDITBOX_ADD_CHAR_EVENT_ACTION_COUNT?eval??>
			if (objMsg == GFX_GOL_EDITBOX_ACTION_ADD_CHAR)
            {
				// EditBox Add Character Event Code
				<#assign count="${GFX_EDITBOX_ADD_CHAR_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_EDITBOX_${GFX_EDITBOX_INDEX}_EVENT_ADD_CHAR_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			<#if GFX_EDITBOX_DEL_CHAR_EVENT_ACTION_COUNT?eval??>
            if (objMsg == GFX_GOL_EDITBOX_ACTION_DEL_CHAR)
            {
                // EditBox Delete Character Event Code
                <#assign count="${GFX_EDITBOX_DEL_CHAR_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_EDITBOX_${GFX_EDITBOX_INDEX}_EVENT_DEL_CHAR_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			<#if GFX_EDITBOX_TOUCHSCREEN_EVENT_ACTION_COUNT?eval??>
            if (objMsg == GFX_GOL_EDITBOX_ACTION_TOUCHSCREEN)
            {
                // EditBox Touch Event Code
                <#assign count="${GFX_EDITBOX_TOUCHSCREEN_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_EDITBOX_${GFX_EDITBOX_INDEX}_EVENT_TOUCHSCREEN_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			
            return true;
</#macro>

<#macro GFX_HGC_LISTBOX_GENERATE_EVENTS
			GFX_LISTBOX_ID
			GFX_INDEX
			GFX_LISTBOX_INDEX
			GFX_LISTBOX_TOUCH_EVENT_ACTION_COUNT
			GFX_LISTBOX_MOVE_EVENT_ACTION_COUNT
			GFX_LISTBOX_SELECTED_EVENT_ACTION_COUNT>
        case <#noparse>${</#noparse>${GFX_LISTBOX_ID}<#noparse>}</#noparse>:
			<#if GFX_LISTBOX_TOUCH_EVENT_ACTION_COUNT?eval??>
			if (objMsg == GFX_GOL_LISTBOX_ACTION_TOUCHSCREEN)
            {
				// ListBox Touch Event Code
				<#assign count="${GFX_LISTBOX_TOUCH_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_LISTBOX_${GFX_LISTBOX_INDEX}_EVENT_TOUCH_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			<#if GFX_LISTBOX_MOVE_EVENT_ACTION_COUNT?eval??>
            if (objMsg == GFX_GOL_LISTBOX_ACTION_MOVE)
            {
                // ListBox Move Event Code
                <#assign count="${GFX_LISTBOX_MOVE_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_LISTBOX_${GFX_LISTBOX_INDEX}_EVENT_MOVE_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			<#if GFX_LISTBOX_SELECTED_EVENT_ACTION_COUNT?eval??>
            if (objMsg == GFX_GOL_LISTBOX_ACTION_SELECTED)
            {
                // ListBox Selected Event Code
                <#assign count="${GFX_LISTBOX_SELECTED_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_LISTBOX_${GFX_LISTBOX_INDEX}_EVENT_SELECTED_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			
            return true;
</#macro>

<#macro GFX_HGC_GROUPBOX_GENERATE_EVENTS
			GFX_GROUPBOX_ID
			GFX_INDEX
			GFX_GROUPBOX_INDEX
			GFX_GROUPBOX_SELECTED_EVENT_ACTION_COUNT>
        case <#noparse>${</#noparse>${GFX_GROUPBOX_ID}<#noparse>}</#noparse>:
			<#if GFX_GROUPBOX_SELECTED_EVENT_ACTION_COUNT?eval??>
            if (objMsg == GFX_GOL_GROUPBOX_ACTION_SELECTED)
            {
                // GroupBox Selected Event Code
                <#assign count="${GFX_GROUPBOX_SELECTED_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_GROUPBOX_${GFX_GROUPBOX_INDEX}_EVENT_SELECTED_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			
            return true;
</#macro>

<#macro GFX_HGC_PICTURE_GENERATE_EVENTS
			GFX_PICTURE_ID
			GFX_INDEX
			GFX_PICTURE_INDEX
			GFX_PICTURE_SELECTED_EVENT_ACTION_COUNT>
        case <#noparse>${</#noparse>${GFX_PICTURE_ID}<#noparse>}</#noparse>:
			<#if GFX_PICTURE_SELECTED_EVENT_ACTION_COUNT?eval??>
			if (objMsg == GFX_GOL_PICTURECONTROL_ACTION_SELECTED)
            {
				// Picture Selected Event Code
				<#assign count="${GFX_PICTURE_SELECTED_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_PICTURE_${GFX_PICTURE_INDEX}_EVENT_SELECTED_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			
            return true;
</#macro>

<#macro GFX_HGC_STATICTEXT_GENERATE_EVENTS
			GFX_STATICTEXT_ID
			GFX_INDEX
			GFX_STATICTEXT_INDEX
			GFX_STATICTEXT_SELECTED_EVENT_ACTION_COUNT>
        case <#noparse>${</#noparse>${GFX_STATICTEXT_ID}<#noparse>}</#noparse>:
			<#if GFX_STATICTEXT_SELECTED_EVENT_ACTION_COUNT?eval??>
			if (objMsg == GFX_GOL_STATICTEXT_ACTION_SELECTED)
            {
				// Static Text Selected Event Code
				<#assign count="${GFX_STATICTEXT_SELECTED_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_STATICTEXT_${GFX_STATICTEXT_INDEX}_EVENT_SELECTED_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			
            return true;
</#macro>

<#macro GFX_HGC_PROGRESSBAR_GENERATE_EVENTS
			GFX_PROGRESSBAR_ID
			GFX_INDEX
			GFX_PROGRESSBAR_INDEX
			GFX_PROGRESSBAR_SELECTED_EVENT_ACTION_COUNT>
        case <#noparse>${</#noparse>${GFX_PROGRESSBAR_ID}<#noparse>}</#noparse>:
			<#if GFX_PROGRESSBAR_SELECTED_EVENT_ACTION_COUNT?eval??>
			if (objMsg == GFX_GOL_PROGRESSBAR_ACTION_SELECTED)
            {
				// ProgressBar Selected Event Code
				<#assign count="${GFX_PROGRESSBAR_SELECTED_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_PROGRESSBAR_${GFX_PROGRESSBAR_INDEX}_EVENT_SELECTED_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			
            return true;
</#macro>

<#macro GFX_HGC_WINDOW_GENERATE_EVENTS
			GFX_WINDOW_ID
			GFX_INDEX
			GFX_WINDOW_INDEX
			GFX_WINDOW_TITLE_EVENT_ACTION_COUNT
			GFX_WINDOW_CLIENT_EVENT_ACTION_COUNT>
        case <#noparse>${</#noparse>${GFX_WINDOW_ID}<#noparse>}</#noparse>:
			<#if GFX_WINDOW_TITLE_EVENT_ACTION_COUNT?eval??>
			if (objMsg == GFX_GOL_WINDOW_ACTION_TITLE)
            {
				// Window Title Touched Event Code
				<#assign count="${GFX_WINDOW_TITLE_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_WINDOW_${GFX_WINDOW_INDEX}_EVENT_TITLE_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			<#if GFX_WINDOW_CLIENT_EVENT_ACTION_COUNT?eval??>
            if (objMsg == GFX_GOL_WINDOW_ACTION_CLIENT)
            {
                // Window Client Touched Event Code
                <#assign count="${GFX_WINDOW_CLIENT_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_WINDOW_${GFX_WINDOW_INDEX}_EVENT_CLIENT_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			
            return true;
</#macro>

<#macro GFX_HGC_TEXTENTRY_GENERATE_EVENTS
			GFX_TEXTENTRY_ID
			GFX_INDEX
			GFX_TEXTENTRY_INDEX
			GFX_TEXTENTRY_PRESS_EVENT_ACTION_COUNT
			GFX_TEXTENTRY_RELEASED_EVENT_ACTION_COUNT
			GFX_TEXTENTRY_ADD_CHAR_EVENT_ACTION_COUNT
			GFX_TEXTENTRY_DELETE_EVENT_ACTION_COUNT
			GFX_TEXTENTRY_SPACE_EVENT_ACTION_COUNT
			GFX_TEXTENTRY_ENTER_EVENT_ACTION_COUNT>
        case <#noparse>${</#noparse>${GFX_TEXTENTRY_ID}<#noparse>}</#noparse>:
			<#if GFX_TEXTENTRY_PRESS_EVENT_ACTION_COUNT?eval??>
			if (objMsg == GFX_GOL_TEXTENTRY_ACTION_PRESSED)
            {
				// Text Entry Press Event Code
				<#assign count="${GFX_TEXTENTRY_PRESS_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_TEXTENTRY_${GFX_TEXTENTRY_INDEX}_EVENT_PRESS_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			<#if GFX_TEXTENTRY_RELEASED_EVENT_ACTION_COUNT?eval??>
			if (objMsg == GFX_GOL_TEXTENTRY_ACTION_RELEASED)
            {
				// Text Entry Released Event Code
				<#assign count="${GFX_TEXTENTRY_RELEASED_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_TEXTENTRY_${GFX_TEXTENTRY_INDEX}_EVENT_RELEASED_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			<#if GFX_TEXTENTRY_ADD_CHAR_EVENT_ACTION_COUNT?eval??>
			if (objMsg == GFX_GOL_TEXTENTRY_ACTION_ADD_CHAR)
            {
				// Text Entry Add Character Event Code
				<#assign count="${GFX_TEXTENTRY_ADD_CHAR_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_TEXTENTRY_${GFX_TEXTENTRY_INDEX}_EVENT_ADD_CHAR_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			<#if GFX_TEXTENTRY_DELETE_EVENT_ACTION_COUNT?eval??>
			if (objMsg == GFX_GOL_TEXTENTRY_ACTION_DELETE)
            {
				// Text Entry Delete Event Code
				<#assign count="${GFX_TEXTENTRY_DELETE_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_TEXTENTRY_${GFX_TEXTENTRY_INDEX}_EVENT_DELETE_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			<#if GFX_TEXTENTRY_SPACE_EVENT_ACTION_COUNT?eval??>
			if (objMsg == GFX_GOL_TEXTENTRY_ACTION_SPACE)
            {
				// Text Entry Space Event Code
				<#assign count="${GFX_TEXTENTRY_SPACE_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_TEXTENTRY_${GFX_TEXTENTRY_INDEX}_EVENT_SPACE_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			<#if GFX_TEXTENTRY_ENTER_EVENT_ACTION_COUNT?eval??>
			if (objMsg == GFX_GOL_TEXTENTRY_ACTION_ENTER)
            {
				// Text Entry Enter Event Code
				<#assign count="${GFX_TEXTENTRY_ENTER_EVENT_ACTION_COUNT}"?eval>
				<#list 0..count?number-1 as ACTION>
				<@GFX_HGC_GENERATE_ACTION
				    GFX_INDEX = GFX_INDEX
					ACTION_ID = "CONFIG_HGC_TEXTENTRY_${GFX_TEXTENTRY_INDEX}_EVENT_ENTER_ACTION_${ACTION}"
					/>
				<#if ACTION < count?number-1>
				
				</#if>
				</#list>
            }
			</#if>
			
            return true;
</#macro>

<#macro GFX_HGC_SCHEME_DECLARE GFX_SCHEME_INDEX>
static GFX_GOL_OBJ_SCHEME *gfxScheme${GFX_SCHEME_INDEX};
</#macro>

<#macro GFX_HGC_SCHEME_INIT
			INDEX
			GFX_SCHEME_ALPHA
			GFX_SCHEME_PRIMARY_COLOR
			GFX_SCHEME_SECONDARY_COLOR
			GFX_SCHEME_DISABLED_COLOR
			GFX_SCHEME_BACKGROUND_COLOR
			GFX_SCHEME_EMBOSS_SIZE
			GFX_SCHEME_EMBOSS_DARK_COLOR
			GFX_SCHEME_EMBOSS_LIGHT_COLOR
			GFX_SCHEME_TEXT_PRIMARY_COLOR
			GFX_SCHEME_TEXT_SECONDARY_COLOR
			GFX_SCHEME_TEXT_DISABLED_COLOR
			GFX_SCHEME_GRADIENT_START_COLOR
			GFX_SCHEME_GRADIENT_END_COLOR
			GFX_SCHEME_BACKGROUND_OFFSET_TOP
			GFX_SCHEME_BACKGROUND_OFFSET_LEFT
			GFX_SCHEME_FONT_RESOURCE
			GFX_SCHEME_BACK_IMAGE_RESOURCE,
			GFX_SCHEME_FILL_STYLE,
			GFX_SCHEME_BACKGROUND_TYPE>
    gfxScheme${INDEX} = GFX_HGC_SchemeCreate();

#ifndef GFX_CONFIG_ALPHABLEND_DISABLE
    gfxScheme${INDEX}->AlphaValue =        ${GFX_SCHEME_ALPHA};
#endif
    gfxScheme${INDEX}->Color0 =            GFX_RGBConvert(${GFX_SCHEME_PRIMARY_COLOR});
    gfxScheme${INDEX}->Color1 =            GFX_RGBConvert(${GFX_SCHEME_SECONDARY_COLOR});
    gfxScheme${INDEX}->ColorDisabled =     GFX_RGBConvert(${GFX_SCHEME_DISABLED_COLOR});
    gfxScheme${INDEX}->CommonBkColor =     GFX_RGBConvert(${GFX_SCHEME_BACKGROUND_COLOR});
	gfxScheme${INDEX}->EmbossSize =        ${GFX_SCHEME_EMBOSS_SIZE};
    gfxScheme${INDEX}->EmbossDkColor =     GFX_RGBConvert(${GFX_SCHEME_EMBOSS_DARK_COLOR});
    gfxScheme${INDEX}->EmbossLtColor =     GFX_RGBConvert(${GFX_SCHEME_EMBOSS_LIGHT_COLOR});
	gfxScheme${INDEX}->TextColor0 =        GFX_RGBConvert(${GFX_SCHEME_TEXT_PRIMARY_COLOR});
    gfxScheme${INDEX}->TextColor1 =        GFX_RGBConvert(${GFX_SCHEME_TEXT_SECONDARY_COLOR});
    gfxScheme${INDEX}->TextColorDisabled = GFX_RGBConvert(${GFX_SCHEME_TEXT_DISABLED_COLOR});
#ifndef GFX_CONFIG_GRADIENT_DISABLE
	gfxScheme${INDEX}->gradientStartColor = GFX_RGBConvert(${GFX_SCHEME_GRADIENT_START_COLOR});
	gfxScheme${INDEX}->gradientEndColor = GFX_RGBConvert(${GFX_SCHEME_GRADIENT_END_COLOR});
#endif
    gfxScheme${INDEX}->CommonBkLeft =      ${GFX_SCHEME_BACKGROUND_OFFSET_TOP};
    gfxScheme${INDEX}->CommonBkTop =       ${GFX_SCHEME_BACKGROUND_OFFSET_LEFT};
    gfxScheme${INDEX}->pFont =             (GFX_RESOURCE_HDR*)<#noparse>${</#noparse>${GFX_SCHEME_FONT_RESOURCE}<#noparse>}</#noparse>;
    gfxScheme${INDEX}->pCommonBkImage =    (GFX_RESOURCE_HDR*)<#noparse>${</#noparse>${GFX_SCHEME_BACK_IMAGE_RESOURCE}<#noparse>}</#noparse>;
	
	gfxScheme${INDEX}->fillStyle =         ${GFX_SCHEME_FILL_STYLE};
	gfxScheme${INDEX}->CommonBkType =      ${GFX_SCHEME_BACKGROUND_TYPE};

</#macro>

<#macro GFX_HGC_SCHEME_DEF
			INDEX
			GFX_SCHEME_NAME
			GFX_SCHEME_ALPHA
			GFX_SCHEME_BACKGROUND_OFFSET_TOP
			GFX_SCHEME_BACKGROUND_OFFSET_LEFT
			GFX_SCHEME_PRIMARY_COLOR_RED
			GFX_SCHEME_PRIMARY_COLOR_GREEN
			GFX_SCHEME_PRIMARY_COLOR_BLUE
			GFX_SCHEME_SECONDARY_COLOR_RED
			GFX_SCHEME_SECONDARY_COLOR_GREEN
			GFX_SCHEME_SECONDARY_COLOR_BLUE
			GFX_SCHEME_DISABLED_COLOR_RED
			GFX_SCHEME_DISABLED_COLOR_GREEN
			GFX_SCHEME_DISABLED_COLOR_BLUE
			GFX_SCHEME_BACKGROUND_COLOR_RED
			GFX_SCHEME_BACKGROUND_COLOR_GREEN
			GFX_SCHEME_BACKGROUND_COLOR_BLUE
			GFX_SCHEME_EMBOSS_SIZE
			GFX_SCHEME_EMBOSS_LIGHT_COLOR_RED
			GFX_SCHEME_EMBOSS_LIGHT_COLOR_GREEN
			GFX_SCHEME_EMBOSS_LIGHT_COLOR_BLUE
			GFX_SCHEME_EMBOSS_DARK_COLOR_RED
			GFX_SCHEME_EMBOSS_DARK_COLOR_GREEN
			GFX_SCHEME_EMBOSS_DARK_COLOR_BLUE
			GFX_SCHEME_TEXT_PRIMARY_COLOR_RED
			GFX_SCHEME_TEXT_PRIMARY_COLOR_GREEN
			GFX_SCHEME_TEXT_PRIMARY_COLOR_BLUE
			GFX_SCHEME_TEXT_SECONDARY_COLOR_RED
			GFX_SCHEME_TEXT_SECONDARY_COLOR_GREEN
			GFX_SCHEME_TEXT_SECONDARY_COLOR_BLUE
			GFX_SCHEME_TEXT_DISABLED_COLOR_RED
			GFX_SCHEME_TEXT_DISABLED_COLOR_GREEN
			GFX_SCHEME_TEXT_DISABLED_COLOR_BLUE
			GFX_SCHEME_GRADIENT_START_COLOR_RED
			GFX_SCHEME_GRADIENT_START_COLOR_GREEN
			GFX_SCHEME_GRADIENT_START_COLOR_BLUE
			GFX_SCHEME_GRADIENT_END_COLOR_RED
			GFX_SCHEME_GRADIENT_END_COLOR_GREEN
			GFX_SCHEME_GRADIENT_END_COLOR_BLUE
			GFX_SCHEME_FILL_STYLE
			GFX_SCHEME_BACKGROUND_TYPE>

#define GFX_SCHEME_NAME_${INDEX}                       "<#noparse>${</#noparse>${GFX_SCHEME_NAME}<#noparse>}</#noparse>"
#define GFX_SCHEME_ALPHA_${INDEX}                      <#noparse>${</#noparse>${GFX_SCHEME_ALPHA}<#noparse>}</#noparse>

#define GFX_SCHEME_BACKGROUND_OFFSET_TOP_${INDEX}      <#noparse>${</#noparse>${GFX_SCHEME_BACKGROUND_OFFSET_TOP}<#noparse>}</#noparse>
#define GFX_SCHEME_BACKGROUND_OFFSET_LEFT_${INDEX}     <#noparse>${</#noparse>${GFX_SCHEME_BACKGROUND_OFFSET_LEFT}<#noparse>}</#noparse>

#define GFX_SCHEME_PRIMARY_COLOR_RED_${INDEX}          <#noparse>${</#noparse>${GFX_SCHEME_PRIMARY_COLOR_RED}<#noparse>}</#noparse>
#define GFX_SCHEME_PRIMARY_COLOR_GREEN_${INDEX}        <#noparse>${</#noparse>${GFX_SCHEME_PRIMARY_COLOR_GREEN}<#noparse>}</#noparse>
#define GFX_SCHEME_PRIMARY_COLOR_BLUE_${INDEX}         <#noparse>${</#noparse>${GFX_SCHEME_PRIMARY_COLOR_BLUE}<#noparse>}</#noparse>

#define GFX_SCHEME_SECONDARY_COLOR_RED_${INDEX}        <#noparse>${</#noparse>${GFX_SCHEME_SECONDARY_COLOR_RED}<#noparse>}</#noparse>
#define GFX_SCHEME_SECONDARY_COLOR_GREEN_${INDEX}      <#noparse>${</#noparse>${GFX_SCHEME_SECONDARY_COLOR_GREEN}<#noparse>}</#noparse>
#define GFX_SCHEME_SECONDARY_COLOR_BLUE_${INDEX}       <#noparse>${</#noparse>${GFX_SCHEME_SECONDARY_COLOR_BLUE}<#noparse>}</#noparse>

#define GFX_SCHEME_DISABLED_COLOR_RED_${INDEX}         <#noparse>${</#noparse>${GFX_SCHEME_DISABLED_COLOR_RED}<#noparse>}</#noparse>
#define GFX_SCHEME_DISABLED_COLOR_GREEN_${INDEX}       <#noparse>${</#noparse>${GFX_SCHEME_DISABLED_COLOR_GREEN}<#noparse>}</#noparse>
#define GFX_SCHEME_DISABLED_COLOR_BLUE_${INDEX}        <#noparse>${</#noparse>${GFX_SCHEME_DISABLED_COLOR_BLUE}<#noparse>}</#noparse>

#define GFX_SCHEME_BACKGROUND_COLOR_RED_${INDEX}       <#noparse>${</#noparse>${GFX_SCHEME_BACKGROUND_COLOR_RED}<#noparse>}</#noparse>
#define GFX_SCHEME_BACKGROUND_COLOR_GREEN_${INDEX}     <#noparse>${</#noparse>${GFX_SCHEME_BACKGROUND_COLOR_GREEN}<#noparse>}</#noparse>
#define GFX_SCHEME_BACKGROUND_COLOR_BLUE_${INDEX}      <#noparse>${</#noparse>${GFX_SCHEME_BACKGROUND_COLOR_BLUE}<#noparse>}</#noparse>

#define GFX_SCHEME_EMBOSS_SIZE_${INDEX}                <#noparse>${</#noparse>${GFX_SCHEME_EMBOSS_SIZE}<#noparse>}</#noparse>

#define GFX_SCHEME_EMBOSS_LIGHT_COLOR_RED_${INDEX}     <#noparse>${</#noparse>${GFX_SCHEME_EMBOSS_LIGHT_COLOR_RED}<#noparse>}</#noparse>
#define GFX_SCHEME_EMBOSS_LIGHT_COLOR_GREEN_${INDEX}   <#noparse>${</#noparse>${GFX_SCHEME_EMBOSS_LIGHT_COLOR_GREEN}<#noparse>}</#noparse>
#define GFX_SCHEME_EMBOSS_LIGHT_COLOR_BLUE_${INDEX}    <#noparse>${</#noparse>${GFX_SCHEME_EMBOSS_LIGHT_COLOR_BLUE}<#noparse>}</#noparse>

#define GFX_SCHEME_EMBOSS_DARK_COLOR_RED_${INDEX}      <#noparse>${</#noparse>${GFX_SCHEME_EMBOSS_DARK_COLOR_RED}<#noparse>}</#noparse>
#define GFX_SCHEME_EMBOSS_DARK_COLOR_GREEN_${INDEX}    <#noparse>${</#noparse>${GFX_SCHEME_EMBOSS_DARK_COLOR_GREEN}<#noparse>}</#noparse>
#define GFX_SCHEME_EMBOSS_DARK_COLOR_BLUE_${INDEX}     <#noparse>${</#noparse>${GFX_SCHEME_EMBOSS_DARK_COLOR_BLUE}<#noparse>}</#noparse>

#define GFX_SCHEME_TEXT_PRIMARY_COLOR_RED_${INDEX}     <#noparse>${</#noparse>${GFX_SCHEME_TEXT_PRIMARY_COLOR_RED}<#noparse>}</#noparse>
#define GFX_SCHEME_TEXT_PRIMARY_COLOR_GREEN_${INDEX}   <#noparse>${</#noparse>${GFX_SCHEME_TEXT_PRIMARY_COLOR_GREEN}<#noparse>}</#noparse>
#define GFX_SCHEME_TEXT_PRIMARY_COLOR_BLUE_${INDEX}    <#noparse>${</#noparse>${GFX_SCHEME_TEXT_PRIMARY_COLOR_BLUE}<#noparse>}</#noparse>

#define GFX_SCHEME_TEXT_SECONDARY_COLOR_RED_${INDEX}   <#noparse>${</#noparse>${GFX_SCHEME_TEXT_SECONDARY_COLOR_RED}<#noparse>}</#noparse>
#define GFX_SCHEME_TEXT_SECONDARY_COLOR_GREEN_${INDEX} <#noparse>${</#noparse>${GFX_SCHEME_TEXT_SECONDARY_COLOR_GREEN}<#noparse>}</#noparse>
#define GFX_SCHEME_TEXT_SECONDARY_COLOR_BLUE_${INDEX}  <#noparse>${</#noparse>${GFX_SCHEME_TEXT_SECONDARY_COLOR_BLUE}<#noparse>}</#noparse>

#define GFX_SCHEME_TEXT_DISABLED_COLOR_RED_${INDEX}    <#noparse>${</#noparse>${GFX_SCHEME_TEXT_DISABLED_COLOR_RED}<#noparse>}</#noparse>
#define GFX_SCHEME_TEXT_DISABLED_COLOR_GREEN_${INDEX}  <#noparse>${</#noparse>${GFX_SCHEME_TEXT_DISABLED_COLOR_GREEN}<#noparse>}</#noparse>
#define GFX_SCHEME_TEXT_DISABLED_COLOR_BLUE_${INDEX}   <#noparse>${</#noparse>${GFX_SCHEME_TEXT_DISABLED_COLOR_BLUE}<#noparse>}</#noparse>

#define GFX_SCHEME_GRADIENT_START_COLOR_RED_${INDEX}    <#noparse>${</#noparse>${GFX_SCHEME_GRADIENT_START_COLOR_RED}<#noparse>}</#noparse>
#define GFX_SCHEME_GRADIENT_START_COLOR_GREEN_${INDEX}  <#noparse>${</#noparse>${GFX_SCHEME_GRADIENT_START_COLOR_GREEN}<#noparse>}</#noparse>
#define GFX_SCHEME_GRADIENT_START_COLOR_BLUE_${INDEX}   <#noparse>${</#noparse>${GFX_SCHEME_GRADIENT_START_COLOR_BLUE}<#noparse>}</#noparse>

#define GFX_SCHEME_GRADIENT_END_COLOR_RED_${INDEX}    <#noparse>${</#noparse>${GFX_SCHEME_GRADIENT_END_COLOR_RED}<#noparse>}</#noparse>
#define GFX_SCHEME_GRADIENT_END_COLOR_GREEN_${INDEX}  <#noparse>${</#noparse>${GFX_SCHEME_GRADIENT_END_COLOR_GREEN}<#noparse>}</#noparse>
#define GFX_SCHEME_GRADIENT_END_COLOR_BLUE_${INDEX}   <#noparse>${</#noparse>${GFX_SCHEME_GRADIENT_END_COLOR_BLUE}<#noparse>}</#noparse>

#define GFX_SCHEME_FILL_STYLE_${INDEX}                <#noparse>${</#noparse>${GFX_SCHEME_FILL_STYLE}<#noparse>}</#noparse>
#define GFX_SCHEME_BACKGROUND_TYPE_${INDEX}           <#noparse>${</#noparse>${GFX_SCHEME_BACKGROUND_TYPE}<#noparse>}</#noparse>

</#macro>

<#macro GFX_HGC_BUTTON_DEF INDEX GFX_BUTTON_LEFT GFX_BUTTON_TOP GFX_BUTTON_RIGHT GFX_BUTTON_BOTTOM GFX_BUTTON_TEXT GFX_BUTTON_ALIGNMENT GFX_BUTTON_RADIUS GFX_BUTTON_STATE GFX_BUTTON_PRESS_IMAGE GFX_BUTTON_RELEASE_IMAGE GFX_BUTTON_SCHEME>
#define GFX_BUTTON_LEFT_${INDEX}            <#noparse>${</#noparse>${GFX_BUTTON_LEFT}<#noparse>}</#noparse>
#define GFX_BUTTON_TOP_${INDEX}             <#noparse>${</#noparse>${GFX_BUTTON_TOP}<#noparse>}</#noparse>
#define GFX_BUTTON_RIGHT_${INDEX}           <#noparse>${</#noparse>${GFX_BUTTON_RIGHT}<#noparse>}</#noparse>
#define GFX_BUTTON_BOTTOM_${INDEX}          <#noparse>${</#noparse>${GFX_BUTTON_BOTTOM}<#noparse>}</#noparse>
#define GFX_BUTTON_TEXT_${INDEX}            "<#noparse>${</#noparse>${GFX_BUTTON_TEXT}<#noparse>}</#noparse>"
#define GFX_BUTTON_ALIGNMENT_${INDEX}       <#noparse>${</#noparse>${GFX_BUTTON_ALIGNMENT}<#noparse>}</#noparse>
#define GFX_BUTTON_RADIUS_${INDEX}          <#noparse>${</#noparse>${GFX_BUTTON_RADIUS}<#noparse>}</#noparse>
#define GFX_BUTTON_STATE_${INDEX}           <#noparse>${</#noparse>${GFX_BUTTON_STATE}<#noparse>}</#noparse>
#define GFX_BUTTON_PRESS_IMAGE_${INDEX}     <#noparse>${</#noparse>${GFX_BUTTON_PRESS_IMAGE}<#noparse>}</#noparse>
#define GFX_BUTTON_RELEASE_IMAGE_${INDEX}   <#noparse>${</#noparse>${GFX_BUTTON_RELEASE_IMAGE}<#noparse>}</#noparse>
#define GFX_BUTTON_SCHEME_${INDEX}          <#noparse>${</#noparse>${GFX_BUTTON_SCHEME}<#noparse>}</#noparse>
</#macro>

<#macro GFX_HGC_BUTTON_ID_DEF ID VALUE>
#define <#noparse>${</#noparse>${ID}<#noparse>}</#noparse>                  ${VALUE} 
</#macro>

<#macro GFX_HGC_BUTTON_EXTERN_DEF ID>
    GFX_GOL_BUTTON* p<#noparse>${</#noparse>${ID}<#noparse>}</#noparse>Obj;
</#macro>

<#macro GFX_HGC_DGTL_MTR_DEF INDEX GFX_DGTL_MTR_LEFT GFX_DGTL_MTR_TOP GFX_DGTL_MTR_RIGHT GFX_DGTL_MTR_BOTTOM GFX_DGTL_MTR_STATE GFX_DGTL_MTR_VALUE GFX_DGTL_MTR_NO_OF_DIGITS GFX_DGTL_MTR_DOT_POSITION GFX_DGTL_MTR_ALIGNMENT GFX_DGTL_MTR_SCHEME>

#define GFX_DGTL_MTR_LEFT_${INDEX}            <#noparse>${</#noparse>${GFX_DGTL_MTR_LEFT}<#noparse>}</#noparse>
#define GFX_DGTL_MTR_TOP_${INDEX}             <#noparse>${</#noparse>${GFX_DGTL_MTR_TOP}<#noparse>}</#noparse>
#define GFX_DGTL_MTR_RIGHT_${INDEX}           <#noparse>${</#noparse>${GFX_DGTL_MTR_RIGHT}<#noparse>}</#noparse>
#define GFX_DGTL_MTR_BOTTOM_${INDEX}          <#noparse>${</#noparse>${GFX_DGTL_MTR_BOTTOM}<#noparse>}</#noparse>
#define GFX_DGTL_MTR_STATE_${INDEX}           <#noparse>${</#noparse>${GFX_DGTL_MTR_STATE}<#noparse>}</#noparse>
#define GFX_DGTL_MTR_VALUE_${INDEX}           <#noparse>${</#noparse>${GFX_DGTL_MTR_VALUE}<#noparse>}</#noparse>
#define GFX_DGTL_MTR_NO_OF_DIGITS_${INDEX}    <#noparse>${</#noparse>${GFX_DGTL_MTR_NO_OF_DIGITS}<#noparse>}</#noparse>
#define GFX_DGTL_MTR_DOT_POSITION_${INDEX}    <#noparse>${</#noparse>${GFX_DGTL_MTR_DOT_POSITION}<#noparse>}</#noparse>
#define GFX_DGTL_MTR_ALIGNMENT_${INDEX}       <#noparse>${</#noparse>${GFX_DGTL_MTR_ALIGNMENT}<#noparse>}</#noparse>
#define GFX_DGTL_MTR_SCHEME_${INDEX}          <#noparse>${</#noparse>${GFX_DGTL_MTR_SCHEME}<#noparse>}</#noparse>
</#macro>

<#macro GFX_HGC_DGTL_MTR_ID_DEF ID VALUE>
#define <#noparse>${</#noparse>${ID}<#noparse>}</#noparse>                  ${VALUE} 
</#macro>

<#macro GFX_HGC_DGTL_MTR_EXTERN_DEF ID>
    GFX_GOL_DIGITALMETER* p<#noparse>${</#noparse>${ID}<#noparse>}</#noparse>Obj;
</#macro>

<#macro GFX_HGC_CHECKBOX_DEF INDEX GFX_CHECKBOX_LEFT GFX_CHECKBOX_TOP GFX_CHECKBOX_RIGHT GFX_CHECKBOX_BOTTOM GFX_CHECKBOX_TEXT GFX_CHECKBOX_STATE GFX_CHECKBOX_ALIGNMENT GFX_CHECKBOX_SCHEME>

#define GFX_CHECKBOX_LEFT_${INDEX}            <#noparse>${</#noparse>${GFX_CHECKBOX_LEFT}<#noparse>}</#noparse>
#define GFX_CHECKBOX_TOP_${INDEX}             <#noparse>${</#noparse>${GFX_CHECKBOX_TOP}<#noparse>}</#noparse>
#define GFX_CHECKBOX_RIGHT_${INDEX}           <#noparse>${</#noparse>${GFX_CHECKBOX_RIGHT}<#noparse>}</#noparse>
#define GFX_CHECKBOX_BOTTOM_${INDEX}          <#noparse>${</#noparse>${GFX_CHECKBOX_BOTTOM}<#noparse>}</#noparse>
#define GFX_CHECKBOX_TEXT_${INDEX}            "<#noparse>${</#noparse>${GFX_CHECKBOX_TEXT}<#noparse>}</#noparse>"
#define GFX_CHECKBOX_STATE_${INDEX}    		  <#noparse>${</#noparse>${GFX_CHECKBOX_STATE}<#noparse>}</#noparse>
#define GFX_CHECKBOX_ALIGNMENT_${INDEX}       <#noparse>${</#noparse>${GFX_CHECKBOX_ALIGNMENT}<#noparse>}</#noparse>
#define GFX_CHECKBOX_SCHEME_${INDEX}          <#noparse>${</#noparse>${GFX_CHECKBOX_SCHEME}<#noparse>}</#noparse>
</#macro>

<#macro GFX_HGC_CHECKBOX_ID_DEF ID VALUE>
#define <#noparse>${</#noparse>${ID}<#noparse>}</#noparse>                  ${VALUE} 
</#macro>

<#macro GFX_HGC_CHECKBOX_EXTERN_DEF ID>
    GFX_GOL_CHECKBOX* p<#noparse>${</#noparse>${ID}<#noparse>}</#noparse>Obj;
</#macro>

<#macro GFX_HGC_RADIOBUTTON_DEF INDEX GFX_RADIOBUTTON_LEFT GFX_RADIOBUTTON_TOP GFX_RADIOBUTTON_RIGHT GFX_RADIOBUTTON_BOTTOM GFX_RADIOBUTTON_TEXT GFX_RADIOBUTTON_STATE GFX_RADIOBUTTON_ALIGNMENT GFX_RADIOBUTTON_SCHEME GFX_RADIOBUTTON_GROUPNO GFX_RADIOBUTTON_NUM_GROUPS_ON_SCREEN>

#define GFX_RADIOBUTTON_LEFT_${INDEX}            <#noparse>${</#noparse>${GFX_RADIOBUTTON_LEFT}<#noparse>}</#noparse>
#define GFX_RADIOBUTTON_TOP_${INDEX}             <#noparse>${</#noparse>${GFX_RADIOBUTTON_TOP}<#noparse>}</#noparse>
#define GFX_RADIOBUTTON_RIGHT_${INDEX}           <#noparse>${</#noparse>${GFX_RADIOBUTTON_RIGHT}<#noparse>}</#noparse>
#define GFX_RADIOBUTTON_BOTTOM_${INDEX}          <#noparse>${</#noparse>${GFX_RADIOBUTTON_BOTTOM}<#noparse>}</#noparse>
#define GFX_RADIOBUTTON_TEXT_${INDEX}            "<#noparse>${</#noparse>${GFX_RADIOBUTTON_TEXT}<#noparse>}</#noparse>"
#define GFX_RADIOBUTTON_STATE_${INDEX}    		  <#noparse>${</#noparse>${GFX_RADIOBUTTON_STATE}<#noparse>}</#noparse>
#define GFX_RADIOBUTTON_ALIGNMENT_${INDEX}       <#noparse>${</#noparse>${GFX_RADIOBUTTON_ALIGNMENT}<#noparse>}</#noparse>
#define GFX_RADIOBUTTON_SCHEME_${INDEX}          <#noparse>${</#noparse>${GFX_RADIOBUTTON_SCHEME}<#noparse>}</#noparse>
#define GFX_RADIOBUTTON_GROUPNO_${INDEX}          <#noparse>${</#noparse>${GFX_RADIOBUTTON_GROUPNO}<#noparse>}</#noparse>
#define GFX_RADIOBUTTON_NUM_GROUPS_ON_SCREEN_${INDEX}   <#noparse>${</#noparse>${GFX_RADIOBUTTON_NUM_GROUPS_ON_SCREEN}<#noparse>}</#noparse>
</#macro>

<#macro GFX_HGC_RADIOBUTTON_ID_DEF ID VALUE>
#define <#noparse>${</#noparse>${ID}<#noparse>}</#noparse>                  ${VALUE} 
</#macro>

<#macro GFX_HGC_RADIOBUTTON_EXTERN_DEF ID>
    GFX_GOL_RADIOBUTTON* p<#noparse>${</#noparse>${ID}<#noparse>}</#noparse>Obj;
</#macro>

<#macro GFX_HGC_SCROLLBAR_DEF INDEX GFX_SCROLLBAR_LEFT GFX_SCROLLBAR_TOP GFX_SCROLLBAR_RIGHT GFX_SCROLLBAR_BOTTOM GFX_SCROLLBAR_STATE GFX_SCROLLBAR_RANGE GFX_SCROLLBAR_PAGE GFX_SCROLLBAR_POS GFX_SCROLLBAR_SCHEME>
#define GFX_SCROLLBAR_LEFT_${INDEX}            	<#noparse>${</#noparse>${GFX_SCROLLBAR_LEFT}<#noparse>}</#noparse>
#define GFX_SCROLLBAR_TOP_${INDEX}             	<#noparse>${</#noparse>${GFX_SCROLLBAR_TOP}<#noparse>}</#noparse>
#define GFX_SCROLLBAR_RIGHT_${INDEX}           	<#noparse>${</#noparse>${GFX_SCROLLBAR_RIGHT}<#noparse>}</#noparse>
#define GFX_SCROLLBAR_BOTTOM_${INDEX}          	<#noparse>${</#noparse>${GFX_SCROLLBAR_BOTTOM}<#noparse>}</#noparse>
#define GFX_SCROLLBAR_STATE_${INDEX}            <#noparse>${</#noparse>${GFX_SCROLLBAR_STATE}<#noparse>}</#noparse>
#define GFX_SCROLLBAR_RANGE_${INDEX}            <#noparse>${</#noparse>${GFX_SCROLLBAR_RANGE}<#noparse>}</#noparse>
#define GFX_SCROLLBAR_PAGE_${INDEX}             <#noparse>${</#noparse>${GFX_SCROLLBAR_PAGE}<#noparse>}</#noparse>
#define GFX_SCROLLBAR_POS_${INDEX}              <#noparse>${</#noparse>${GFX_SCROLLBAR_POS}<#noparse>}</#noparse>
#define GFX_SCROLLBAR_SCHEME_${INDEX}           <#noparse>${</#noparse>${GFX_SCROLLBAR_SCHEME}<#noparse>}</#noparse>
</#macro>

<#macro GFX_HGC_SCROLLBAR_ID_DEF ID VALUE>
#define <#noparse>${</#noparse>${ID}<#noparse>}</#noparse>                  ${VALUE} 
</#macro>

<#macro GFX_HGC_SCROLLBAR_EXTERN_DEF ID>
    GFX_GOL_SCROLLBAR* p<#noparse>${</#noparse>${ID}<#noparse>}</#noparse>Obj;
</#macro>

<#macro GFX_HGC_PROGRESSBAR_DEF INDEX GFX_PROGRESSBAR_LEFT GFX_PROGRESSBAR_TOP GFX_PROGRESSBAR_RIGHT GFX_PROGRESSBAR_BOTTOM GFX_PROGRESSBAR_STATE GFX_PROGRESSBAR_RANGE GFX_PROGRESSBAR_POS GFX_PROGRESSBAR_SCHEME>
#define GFX_PROGRESSBAR_LEFT_${INDEX}            	<#noparse>${</#noparse>${GFX_PROGRESSBAR_LEFT}<#noparse>}</#noparse>
#define GFX_PROGRESSBAR_TOP_${INDEX}             	<#noparse>${</#noparse>${GFX_PROGRESSBAR_TOP}<#noparse>}</#noparse>
#define GFX_PROGRESSBAR_RIGHT_${INDEX}           	<#noparse>${</#noparse>${GFX_PROGRESSBAR_RIGHT}<#noparse>}</#noparse>
#define GFX_PROGRESSBAR_BOTTOM_${INDEX}          	<#noparse>${</#noparse>${GFX_PROGRESSBAR_BOTTOM}<#noparse>}</#noparse>
#define GFX_PROGRESSBAR_STATE_${INDEX}            <#noparse>${</#noparse>${GFX_PROGRESSBAR_STATE}<#noparse>}</#noparse>
#define GFX_PROGRESSBAR_RANGE_${INDEX}            <#noparse>${</#noparse>${GFX_PROGRESSBAR_RANGE}<#noparse>}</#noparse>
#define GFX_PROGRESSBAR_POS_${INDEX}              <#noparse>${</#noparse>${GFX_PROGRESSBAR_POS}<#noparse>}</#noparse>
#define GFX_PROGRESSBAR_SCHEME_${INDEX}           <#noparse>${</#noparse>${GFX_PROGRESSBAR_SCHEME}<#noparse>}</#noparse>
</#macro>

<#macro GFX_HGC_PROGRESSBAR_ID_DEF ID VALUE>
#define <#noparse>${</#noparse>${ID}<#noparse>}</#noparse>                  ${VALUE} 
</#macro>

<#macro GFX_HGC_PROGRESSBAR_EXTERN_DEF ID>
    GFX_GOL_PROGRESSBAR* p<#noparse>${</#noparse>${ID}<#noparse>}</#noparse>Obj;
</#macro>

<#macro GFX_HGC_METER_DEF INDEX GFX_METER_LEFT GFX_METER_TOP GFX_METER_RIGHT GFX_METER_BOTTOM GFX_METER_STATE GFX_METER_VALUE GFX_METER_MINVALUE GFX_METER_MAXVALUE GFX_METER_TYPE GFX_METER_SCHEME
GFX_METER_COLOR1_RED GFX_METER_COLOR1_GREEN GFX_METER_COLOR1_BLUE
GFX_METER_COLOR2_RED GFX_METER_COLOR2_GREEN GFX_METER_COLOR2_BLUE
GFX_METER_COLOR3_RED GFX_METER_COLOR3_GREEN GFX_METER_COLOR3_BLUE
GFX_METER_COLOR4_RED GFX_METER_COLOR4_GREEN GFX_METER_COLOR4_BLUE
GFX_METER_COLOR5_RED GFX_METER_COLOR5_GREEN GFX_METER_COLOR5_BLUE
GFX_METER_COLOR6_RED GFX_METER_COLOR6_GREEN GFX_METER_COLOR6_BLUE>
#define GFX_METER_LEFT_${INDEX}            	<#noparse>${</#noparse>${GFX_METER_LEFT}<#noparse>}</#noparse>
#define GFX_METER_TOP_${INDEX}             	<#noparse>${</#noparse>${GFX_METER_TOP}<#noparse>}</#noparse>
#define GFX_METER_RIGHT_${INDEX}           	<#noparse>${</#noparse>${GFX_METER_RIGHT}<#noparse>}</#noparse>
#define GFX_METER_BOTTOM_${INDEX}          	<#noparse>${</#noparse>${GFX_METER_BOTTOM}<#noparse>}</#noparse>
#define GFX_METER_STATE_${INDEX}            <#noparse>${</#noparse>${GFX_METER_STATE}<#noparse>}</#noparse>
#define GFX_METER_TYPE_${INDEX}             <#noparse>${</#noparse>${GFX_METER_TYPE}<#noparse>}</#noparse>
#define GFX_METER_VALUE_${INDEX}            <#noparse>${</#noparse>${GFX_METER_VALUE}<#noparse>}</#noparse>
#define GFX_METER_MIN_VALUE_${INDEX}        <#noparse>${</#noparse>${GFX_METER_MINVALUE}<#noparse>}</#noparse>
#define GFX_METER_MAX_VALUE_${INDEX}        <#noparse>${</#noparse>${GFX_METER_MAXVALUE}<#noparse>}</#noparse>
#define GFX_METER_SCHEME_${INDEX}           <#noparse>${</#noparse>${GFX_METER_SCHEME}<#noparse>}</#noparse>

#define GFX_METER_COLOR1_RED_${INDEX}       <#noparse>${</#noparse>${GFX_METER_COLOR1_RED}<#noparse>}</#noparse>
#define GFX_METER_COLOR1_GREEN_${INDEX}     <#noparse>${</#noparse>${GFX_METER_COLOR1_GREEN}<#noparse>}</#noparse>
#define GFX_METER_COLOR1_BLUE_${INDEX}      <#noparse>${</#noparse>${GFX_METER_COLOR1_BLUE}<#noparse>}</#noparse>

#define GFX_METER_COLOR2_RED_${INDEX}       <#noparse>${</#noparse>${GFX_METER_COLOR2_RED}<#noparse>}</#noparse>
#define GFX_METER_COLOR2_GREEN_${INDEX}     <#noparse>${</#noparse>${GFX_METER_COLOR2_GREEN}<#noparse>}</#noparse>
#define GFX_METER_COLOR2_BLUE_${INDEX}      <#noparse>${</#noparse>${GFX_METER_COLOR2_BLUE}<#noparse>}</#noparse>

#define GFX_METER_COLOR3_RED_${INDEX}       <#noparse>${</#noparse>${GFX_METER_COLOR3_RED}<#noparse>}</#noparse>
#define GFX_METER_COLOR3_GREEN_${INDEX}     <#noparse>${</#noparse>${GFX_METER_COLOR3_GREEN}<#noparse>}</#noparse>
#define GFX_METER_COLOR3_BLUE_${INDEX}      <#noparse>${</#noparse>${GFX_METER_COLOR3_BLUE}<#noparse>}</#noparse>

#define GFX_METER_COLOR4_RED_${INDEX}       <#noparse>${</#noparse>${GFX_METER_COLOR4_RED}<#noparse>}</#noparse>
#define GFX_METER_COLOR4_GREEN_${INDEX}     <#noparse>${</#noparse>${GFX_METER_COLOR4_GREEN}<#noparse>}</#noparse>
#define GFX_METER_COLOR4_BLUE_${INDEX}      <#noparse>${</#noparse>${GFX_METER_COLOR4_BLUE}<#noparse>}</#noparse>

#define GFX_METER_COLOR5_RED_${INDEX}       <#noparse>${</#noparse>${GFX_METER_COLOR5_RED}<#noparse>}</#noparse>
#define GFX_METER_COLOR5_GREEN_${INDEX}     <#noparse>${</#noparse>${GFX_METER_COLOR5_GREEN}<#noparse>}</#noparse>
#define GFX_METER_COLOR5_BLUE_${INDEX}      <#noparse>${</#noparse>${GFX_METER_COLOR5_BLUE}<#noparse>}</#noparse>

#define GFX_METER_COLOR6_RED_${INDEX}       <#noparse>${</#noparse>${GFX_METER_COLOR6_RED}<#noparse>}</#noparse>
#define GFX_METER_COLOR6_GREEN_${INDEX}     <#noparse>${</#noparse>${GFX_METER_COLOR6_GREEN}<#noparse>}</#noparse>
#define GFX_METER_COLOR6_BLUE_${INDEX}      <#noparse>${</#noparse>${GFX_METER_COLOR6_BLUE}<#noparse>}</#noparse>
</#macro>

<#macro GFX_HGC_METER_ID_DEF ID VALUE>
#define <#noparse>${</#noparse>${ID}<#noparse>}</#noparse>                  ${VALUE} 
</#macro>

<#macro GFX_HGC_METER_EXTERN_DEF ID>
    GFX_GOL_METER* p<#noparse>${</#noparse>${ID}<#noparse>}</#noparse>Obj;
</#macro>

<#macro GFX_HGC_METER_TEXT_INIT INDEX TEXT>
static const GFX_XCHAR meterStr_${INDEX}[] = { <#noparse>${</#noparse>${TEXT}<#noparse>}</#noparse> }; // <#noparse>${CONFIG_HGC_METER_TEXT_STRING_</#noparse>${INDEX}<#noparse>}</#noparse>
</#macro>

<#macro GFX_HGC_EDITBOX_DEF INDEX GFX_EDITBOX_LEFT GFX_EDITBOX_TOP GFX_EDITBOX_RIGHT GFX_EDITBOX_BOTTOM GFX_EDITBOX_STATE GFX_EDITBOX_TEXT GFX_EDITBOX_NOOFCHARS GFX_EDITBOX_ALIGNMENT GFX_EDITBOX_SCHEME>
#define GFX_EDITBOX_LEFT_${INDEX}            <#noparse>${</#noparse>${GFX_EDITBOX_LEFT}<#noparse>}</#noparse>
#define GFX_EDITBOX_TOP_${INDEX}             <#noparse>${</#noparse>${GFX_EDITBOX_TOP}<#noparse>}</#noparse>
#define GFX_EDITBOX_RIGHT_${INDEX}           <#noparse>${</#noparse>${GFX_EDITBOX_RIGHT}<#noparse>}</#noparse>
#define GFX_EDITBOX_BOTTOM_${INDEX}          <#noparse>${</#noparse>${GFX_EDITBOX_BOTTOM}<#noparse>}</#noparse>
#define GFX_EDITBOX_STATE_${INDEX}           <#noparse>${</#noparse>${GFX_EDITBOX_STATE}<#noparse>}</#noparse>
#define GFX_EDITBOX_TEXT_${INDEX}            "<#noparse>${</#noparse>${GFX_EDITBOX_TEXT}<#noparse>}</#noparse>"
#define GFX_EDITBOX_NOOFCHARS_${INDEX}       <#noparse>${</#noparse>${GFX_EDITBOX_NOOFCHARS}<#noparse>}</#noparse>
#define GFX_EDITBOX_ALIGNMENT_${INDEX}       <#noparse>${</#noparse>${GFX_EDITBOX_ALIGNMENT}<#noparse>}</#noparse>
#define GFX_EDITBOX_SCHEME_${INDEX}          <#noparse>${</#noparse>${GFX_EDITBOX_SCHEME}<#noparse>}</#noparse>
</#macro>

<#macro GFX_HGC_EDITBOX_ID_DEF ID VALUE>
#define <#noparse>${</#noparse>${ID}<#noparse>}</#noparse>                  ${VALUE} 
</#macro>

<#macro GFX_HGC_EDITBOX_EXTERN_DEF ID>
    GFX_GOL_EDITBOX* p<#noparse>${</#noparse>${ID}<#noparse>}</#noparse>Obj;
</#macro>

<#macro GFX_HGC_LISTBOX_TEXT_INIT
			NAME
			INDEX
			COUNT>
<#assign count="${COUNT}"?eval?number>
<#if (count > 0)>
<#list 0..count?number-1 as ITEM>
static GFX_XCHAR* <#noparse>${</#noparse>${NAME}<#noparse>}</#noparse>_item_${ITEM}_text = "<#noparse>${CONFIG_HGC_LISTBOX_</#noparse>${INDEX}<#noparse>_ITEM_</#noparse>${ITEM}<#noparse>_TEXT}</#noparse>";
</#list>
</#if>

</#macro>

<#macro GFX_HGC_LISTBOX_DEF 
			INDEX
			GFX_LISTBOX_LEFT
			GFX_LISTBOX_TOP
			GFX_LISTBOX_RIGHT
			GFX_LISTBOX_BOTTOM
			GFX_LISTBOX_STATE
			GFX_LISTBOX_SCHEME
			GFX_LISTBOX_ALIGNMENT
			GFX_LISTBOX_ITEM_COUNT>
#define GFX_LISTBOX_LEFT_${INDEX}            <#noparse>${</#noparse>${GFX_LISTBOX_LEFT}<#noparse>}</#noparse>
#define GFX_LISTBOX_TOP_${INDEX}             <#noparse>${</#noparse>${GFX_LISTBOX_TOP}<#noparse>}</#noparse>
#define GFX_LISTBOX_RIGHT_${INDEX}           <#noparse>${</#noparse>${GFX_LISTBOX_RIGHT}<#noparse>}</#noparse>
#define GFX_LISTBOX_BOTTOM_${INDEX}          <#noparse>${</#noparse>${GFX_LISTBOX_BOTTOM}<#noparse>}</#noparse>
#define GFX_LISTBOX_STATE_${INDEX}           <#noparse>${</#noparse>${GFX_LISTBOX_STATE}<#noparse>}</#noparse>
#define GFX_LISTBOX_SCHEME_${INDEX}          <#noparse>${</#noparse>${GFX_LISTBOX_SCHEME}<#noparse>}</#noparse>
#define GFX_LISTBOX_ALIGNMENT_${INDEX}       <#noparse>${</#noparse>${GFX_LISTBOX_ALIGNMENT}<#noparse>}</#noparse>
#define GFX_LISTBOX_ITEM_COUNT_${INDEX}      <#noparse>${</#noparse>${GFX_LISTBOX_ITEM_COUNT}<#noparse>}</#noparse>

<#assign count="${GFX_LISTBOX_ITEM_COUNT}"?eval?number>
<#if (count > 0)>
<#list 0..count-1 as ITEM>
<#assign val = "CONFIG_HGC_LISTBOX_" + INDEX + "_ITEM_" + ITEM + "_IMAGE">
<#if val?eval != "NULL">
#define GFX_LISTBOX_${INDEX}_ITEM_${ITEM}_IMAGE       <#noparse>${CONFIG_HGC_LISTBOX_</#noparse>${INDEX}<#noparse>_ITEM_</#noparse>${ITEM}<#noparse>_IMAGE}</#noparse>
</#if>
#define GFX_LISTBOX_${INDEX}_ITEM_${ITEM}_USERDATA    <#noparse>${CONFIG_HGC_LISTBOX_</#noparse>${INDEX}<#noparse>_ITEM_</#noparse>${ITEM}<#noparse>_USERDATA}</#noparse>
</#list>
</#if>
</#macro>

<#macro GFX_HGC_LISTBOX_ID_DEF ID VALUE>
#define <#noparse>${</#noparse>${ID}<#noparse>}</#noparse>                  ${VALUE} 
</#macro>

<#macro GFX_HGC_LISTBOX_EXTERN_DEF ID>
    GFX_GOL_LISTBOX* p<#noparse>${</#noparse>${ID}<#noparse>}</#noparse>Obj;
</#macro>

<#macro GFX_HGC_CREATE_LISTBOX
			INDEX
			GFX_INDEX
			GFX_LISTBOX_ID
			GFX_LISTBOX_LEFT
			GFX_LISTBOX_TOP
			GFX_LISTBOX_RIGHT
			GFX_LISTBOX_BOTTOM
			GFX_LISTBOX_STATE
			GFX_LISTBOX_SCHEME
			GFX_LISTBOX_ALIGNMENT
			GFX_LISTBOX_ITEM_COUNT
			GFX_LISTBOX_ITEM_FOCUS>
    case <#noparse>${</#noparse>${GFX_LISTBOX_ID}<#noparse>}</#noparse>:
        hgcObj.p<#noparse>${</#noparse>${GFX_LISTBOX_ID}<#noparse>}</#noparse>Obj = GFX_GOL_ListBoxCreate(
                ${GFX_INDEX},
                <#noparse>${</#noparse>${GFX_LISTBOX_ID}<#noparse>}</#noparse>, // id
                ${GFX_LISTBOX_LEFT}, // left
                ${GFX_LISTBOX_TOP}, // top
                ${GFX_LISTBOX_RIGHT}, // right
                ${GFX_LISTBOX_BOTTOM}, // bottom
				${GFX_LISTBOX_STATE}, // state
				NULL, // default text
                ${GFX_LISTBOX_ALIGNMENT}, //alignment
                ${GFX_LISTBOX_SCHEME}); // scheme
		
<#assign count="${GFX_LISTBOX_ITEM_COUNT}"?eval?number>
<#if (count > 0)>
<#list 0..count-1 as ITEM>
		hgcObj.pListBoxItem = GFX_GOL_ListBoxItemAdd(
				hgcObj.p<#noparse>${</#noparse>${GFX_LISTBOX_ID}<#noparse>}</#noparse>Obj,
<#if ITEM == 0>
				NULL,
<#else>
				hgcObj.pListBoxItem,
</#if>
				<#noparse>${</#noparse>${GFX_LISTBOX_ID}<#noparse>}</#noparse>_item_${ITEM}_text,
<#assign val = "CONFIG_HGC_LISTBOX_" + INDEX + "_ITEM_" + ITEM + "_IMAGE">
<#if val?eval != "NULL">
				(GFX_RESOURCE_HDR*)&GFX_LISTBOX_${INDEX}_ITEM_${ITEM}_IMAGE,
<#else>
				NULL,
</#if>
<#assign focus="${GFX_LISTBOX_ITEM_FOCUS}"?eval>
<#if ITEM == focus?number>
				GFX_GOL_LISTBOX_ITEM_STATUS_SELECTED,
<#else>
				0,
</#if>
				GFX_LISTBOX_${INDEX}_ITEM_${ITEM}_USERDATA);
				
</#list>
</#if>
        break;
</#macro>



<#macro GFX_HGC_GROUPBOX_TEXT_INIT
			NAME
			INDEX>
<#assign val = "CONFIG_HGC_GROUPBOX_TEXT_${INDEX}">
<#if val?eval??>
static GFX_XCHAR* <#noparse>${</#noparse>${NAME}<#noparse>}</#noparse>_text = "<#noparse>${CONFIG_HGC_GROUPBOX_TEXT_</#noparse>${INDEX}<#noparse>}</#noparse>";
</#if>
</#macro>

<#macro GFX_HGC_GROUPBOX_DEF 
			INDEX
			GFX_GROUPBOX_LEFT
			GFX_GROUPBOX_TOP
			GFX_GROUPBOX_RIGHT
			GFX_GROUPBOX_BOTTOM
			GFX_GROUPBOX_STATE
			GFX_GROUPBOX_SCHEME
			GFX_GROUPBOX_ALIGNMENT>
#define GFX_GROUPBOX_LEFT_${INDEX}            <#noparse>${</#noparse>${GFX_GROUPBOX_LEFT}<#noparse>}</#noparse>
#define GFX_GROUPBOX_TOP_${INDEX}             <#noparse>${</#noparse>${GFX_GROUPBOX_TOP}<#noparse>}</#noparse>
#define GFX_GROUPBOX_RIGHT_${INDEX}           <#noparse>${</#noparse>${GFX_GROUPBOX_RIGHT}<#noparse>}</#noparse>
#define GFX_GROUPBOX_BOTTOM_${INDEX}          <#noparse>${</#noparse>${GFX_GROUPBOX_BOTTOM}<#noparse>}</#noparse>
#define GFX_GROUPBOX_STATE_${INDEX}           <#noparse>${</#noparse>${GFX_GROUPBOX_STATE}<#noparse>}</#noparse>
#define GFX_GROUPBOX_SCHEME_${INDEX}          <#noparse>${</#noparse>${GFX_GROUPBOX_SCHEME}<#noparse>}</#noparse>
#define GFX_GROUPBOX_ALIGNMENT_${INDEX}       <#noparse>${</#noparse>${GFX_GROUPBOX_ALIGNMENT}<#noparse>}</#noparse>

</#macro>

<#macro GFX_HGC_GROUPBOX_ID_DEF ID VALUE>
#define <#noparse>${</#noparse>${ID}<#noparse>}</#noparse>                  ${VALUE} 
</#macro>

<#macro GFX_HGC_GROUPBOX_EXTERN_DEF ID>
    GFX_GOL_GROUPBOX* p<#noparse>${</#noparse>${ID}<#noparse>}</#noparse>Obj;
</#macro>

<#macro GFX_HGC_CREATE_GROUPBOX
			INDEX
			GFX_INDEX
			GFX_GROUPBOX_ID
			GFX_GROUPBOX_LEFT
			GFX_GROUPBOX_TOP
			GFX_GROUPBOX_RIGHT
			GFX_GROUPBOX_BOTTOM
			GFX_GROUPBOX_STATE
			GFX_GROUPBOX_SCHEME
			GFX_GROUPBOX_TEXT
			GFX_GROUPBOX_ALIGNMENT>
    case <#noparse>${</#noparse>${GFX_GROUPBOX_ID}<#noparse>}</#noparse>:
        hgcObj.p<#noparse>${</#noparse>${GFX_GROUPBOX_ID}<#noparse>}</#noparse>Obj = GFX_GOL_GroupboxCreate(
                ${GFX_INDEX},
                <#noparse>${</#noparse>${GFX_GROUPBOX_ID}<#noparse>}</#noparse>, // id
                ${GFX_GROUPBOX_LEFT}, // left
                ${GFX_GROUPBOX_TOP}, // top
                ${GFX_GROUPBOX_RIGHT}, // right
                ${GFX_GROUPBOX_BOTTOM}, // bottom
				${GFX_GROUPBOX_STATE}, // state
<#noparse><#if </#noparse>${GFX_GROUPBOX_TEXT}<#noparse>??></#noparse>
				<#noparse>${</#noparse>${GFX_GROUPBOX_ID}<#noparse>}</#noparse>_text, // text
<#noparse><#else></#noparse>
				NULL, // text
<#noparse></#if></#noparse>
                ${GFX_GROUPBOX_ALIGNMENT}, //alignment
                ${GFX_GROUPBOX_SCHEME}); // scheme
				
		break;
		
</#macro>



<#macro GFX_HGC_STATICTEXT_DEF INDEX GFX_STATICTEXT_LEFT GFX_STATICTEXT_TOP GFX_STATICTEXT_RIGHT GFX_STATICTEXT_BOTTOM GFX_STATICTEXT_STATE GFX_STATICTEXT_TEXT GFX_STATICTEXT_ALIGNMENT GFX_STATICTEXT_SCHEME>
#define GFX_STATICTEXT_LEFT_${INDEX}            <#noparse>${</#noparse>${GFX_STATICTEXT_LEFT}<#noparse>}</#noparse>
#define GFX_STATICTEXT_TOP_${INDEX}             <#noparse>${</#noparse>${GFX_STATICTEXT_TOP}<#noparse>}</#noparse>
#define GFX_STATICTEXT_RIGHT_${INDEX}           <#noparse>${</#noparse>${GFX_STATICTEXT_RIGHT}<#noparse>}</#noparse>
#define GFX_STATICTEXT_BOTTOM_${INDEX}          <#noparse>${</#noparse>${GFX_STATICTEXT_BOTTOM}<#noparse>}</#noparse>
#define GFX_STATICTEXT_STATE_${INDEX}          <#noparse>${</#noparse>${GFX_STATICTEXT_STATE}<#noparse>}</#noparse>
#define GFX_STATICTEXT_TEXT_${INDEX}            "<#noparse>${</#noparse>${GFX_STATICTEXT_TEXT}<#noparse>}</#noparse>"
#define GFX_STATICTEXT_ALIGNMENT_${INDEX}       <#noparse>${</#noparse>${GFX_STATICTEXT_ALIGNMENT}<#noparse>}</#noparse>
#define GFX_STATICTEXT_SCHEME_${INDEX}          <#noparse>${</#noparse>${GFX_STATICTEXT_SCHEME}<#noparse>}</#noparse>
</#macro>

<#macro GFX_HGC_STATICTEXT_ID_DEF ID VALUE>
#define <#noparse>${</#noparse>${ID}<#noparse>}</#noparse>                  ${VALUE} 
</#macro>

<#macro GFX_HGC_STATICTEXT_EXTERN_DEF ID>
    GFX_GOL_STATICTEXT* p<#noparse>${</#noparse>${ID}<#noparse>}</#noparse>Obj;
</#macro>



<#macro GFX_HGC_TEXTENTRY_TEXT_INIT
			NAME
			INDEX
			ROW_COUNT
			COL_COUNT>
static GFX_XCHAR <#noparse>${</#noparse>${NAME}<#noparse>}</#noparse>_text[] = { <#noparse>${CONFIG_HGC_TEXTENTRY_TEXT_</#noparse>${INDEX}<#noparse>}</#noparse> };
static GFX_XCHAR* <#noparse>${</#noparse>${NAME}<#noparse>}</#noparse>_cell_text[] =
{
<#assign rows="${ROW_COUNT}"?eval>
<#assign cols="${COL_COUNT}"?eval>
<#list 0..rows?number-1 as ROW>
<#list 0..cols?number-1 as COL>
<#if ROW == rows?number-1 && COL == cols?number-1>
	"<#noparse>${CONFIG_HGC_TEXTENTRY_</#noparse>${INDEX}<#noparse>_CELLTEXT_</#noparse>${ROW}_${COL}<#noparse>}</#noparse>"
<#else>
	"<#noparse>${CONFIG_HGC_TEXTENTRY_</#noparse>${INDEX}<#noparse>_CELLTEXT_</#noparse>${ROW}_${COL}<#noparse>}</#noparse>",
</#if>
</#list>
</#list>
};

</#macro>

<#macro GFX_HGC_TEXTENTRY_DEF 
			INDEX
			GFX_TEXTENTRY_LEFT
			GFX_TEXTENTRY_TOP
			GFX_TEXTENTRY_RIGHT
			GFX_TEXTENTRY_BOTTOM
			GFX_TEXTENTRY_STATE
			GFX_TEXTENTRY_SCHEME
			GFX_TEXTENTRY_BUFFERSIZE
			GFX_TEXTENTRY_FONT_ID
			GFX_TEXTENTRY_ALIGNMENT,
			GFX_TEXTENTRY_ROW_COUNT,
			GFX_TEXTENTRY_COLUMN_COUNT>
#define HGC_TEXTENTRY_LEFT_${INDEX}           <#noparse>${</#noparse>${GFX_TEXTENTRY_LEFT}<#noparse>}</#noparse>
#define HGC_TEXTENTRY_TOP_${INDEX}            <#noparse>${</#noparse>${GFX_TEXTENTRY_TOP}<#noparse>}</#noparse>
#define HGC_TEXTENTRY_RIGHT_${INDEX}          <#noparse>${</#noparse>${GFX_TEXTENTRY_RIGHT}<#noparse>}</#noparse>
#define HGC_TEXTENTRY_BOTTOM_${INDEX}         <#noparse>${</#noparse>${GFX_TEXTENTRY_BOTTOM}<#noparse>}</#noparse>
#define HGC_TEXTENTRY_STATE_${INDEX}          <#noparse>${</#noparse>${GFX_TEXTENTRY_STATE}<#noparse>}</#noparse>
#define HGC_TEXTENTRY_SCHEME_${INDEX}         <#noparse>${</#noparse>${GFX_TEXTENTRY_SCHEME}<#noparse>}</#noparse>
#define HGC_TEXTENTRY_BUFFERSIZE_${INDEX}     <#noparse>${</#noparse>${GFX_TEXTENTRY_BUFFERSIZE}<#noparse>}</#noparse>
#define HGC_TEXTENTRY_ALIGNMENT_${INDEX}      <#noparse>${</#noparse>${GFX_TEXTENTRY_ALIGNMENT}<#noparse>}</#noparse>
#define HGC_TEXTENTRY_ROW_COUNT_${INDEX}      <#noparse>${</#noparse>${GFX_TEXTENTRY_ROW_COUNT}<#noparse>}</#noparse>
#define HGC_TEXTENTRY_COLUMN_COUNT_${INDEX}   <#noparse>${</#noparse>${GFX_TEXTENTRY_COLUMN_COUNT}<#noparse>}</#noparse>

</#macro>

<#macro GFX_HGC_TEXTENTRY_ID_DEF ID VALUE>
#define <#noparse>${</#noparse>${ID}<#noparse>}</#noparse>                  ${VALUE} 
</#macro>

<#macro GFX_HGC_TEXTENTRY_EXTERN_DEF ID>
    GFX_GOL_TEXTENTRY* p<#noparse>${</#noparse>${ID}<#noparse>}</#noparse>Obj;
</#macro>

<#macro GFX_HGC_CREATE_TEXTENTRY
			INDEX
			GFX_INDEX
			GFX_TEXTENTRY_ID
			GFX_TEXTENTRY_LEFT
			GFX_TEXTENTRY_TOP
			GFX_TEXTENTRY_RIGHT
			GFX_TEXTENTRY_BOTTOM
			GFX_TEXTENTRY_STATE
			GFX_TEXTENTRY_SCHEME
			GFX_TEXTENTRY_BUFFERSIZE
			GFX_TEXTENTRY_FONT_ID
			GFX_TEXTENTRY_ALIGNMENT
			GFX_TEXTENTRY_ROW_COUNT
			GFX_TEXTENTRY_COLUMN_COUNT>
    case <#noparse>${</#noparse>${GFX_TEXTENTRY_ID}<#noparse>}</#noparse>:
        hgcObj.p<#noparse>${</#noparse>${GFX_TEXTENTRY_ID}<#noparse>}</#noparse>Obj = GFX_GOL_TextEntryCreate(
                ${GFX_INDEX},
                <#noparse>${</#noparse>${GFX_TEXTENTRY_ID}<#noparse>}</#noparse>, // id
                ${GFX_TEXTENTRY_LEFT}, // left
                ${GFX_TEXTENTRY_TOP}, // top
                ${GFX_TEXTENTRY_RIGHT}, // right
                ${GFX_TEXTENTRY_BOTTOM}, // bottom
				${GFX_TEXTENTRY_STATE}, // state
				${GFX_TEXTENTRY_ROW_COUNT}, // rows
				${GFX_TEXTENTRY_COLUMN_COUNT}, // columns
				<#noparse>${</#noparse>${GFX_TEXTENTRY_ID}<#noparse>}</#noparse>_cell_text, // cell text
				<#noparse>${</#noparse>${GFX_TEXTENTRY_ID}<#noparse>}</#noparse>_text, // initial text
                ${GFX_TEXTENTRY_ALIGNMENT}, //alignment
				${GFX_TEXTENTRY_BUFFERSIZE},
				(GFX_RESOURCE_HDR*)&<#noparse>${</#noparse>${GFX_TEXTENTRY_FONT_ID}<#noparse>}</#noparse>, // font
                ${GFX_TEXTENTRY_SCHEME}); // scheme
				
        break;
</#macro>


<#macro GFX_HGC_WINDOW_DEF INDEX GFX_WINDOW_LEFT GFX_WINDOW_TOP GFX_WINDOW_RIGHT GFX_WINDOW_BOTTOM GFX_WINDOW_STATE GFX_WINDOW_IMAGE GFX_WINDOW_TEXT GFX_WINDOW_ALIGNMENT GFX_WINDOW_SCHEME>
#define GFX_WINDOW_LEFT_${INDEX}            <#noparse>${</#noparse>${GFX_WINDOW_LEFT}<#noparse>}</#noparse>
#define GFX_WINDOW_TOP_${INDEX}             <#noparse>${</#noparse>${GFX_WINDOW_TOP}<#noparse>}</#noparse>
#define GFX_WINDOW_RIGHT_${INDEX}           <#noparse>${</#noparse>${GFX_WINDOW_RIGHT}<#noparse>}</#noparse>
#define GFX_WINDOW_BOTTOM_${INDEX}          <#noparse>${</#noparse>${GFX_WINDOW_BOTTOM}<#noparse>}</#noparse>
#define GFX_WINDOW_STATE_${INDEX}           <#noparse>${</#noparse>${GFX_WINDOW_STATE}<#noparse>}</#noparse>
#define GFX_WINDOW_IMAGE_${INDEX}           <#noparse>${</#noparse>${GFX_WINDOW_IMAGE}<#noparse>}</#noparse>
#define GFX_WINDOW_TEXT_${INDEX}            "<#noparse>${</#noparse>${GFX_WINDOW_TEXT}<#noparse>}</#noparse>"
#define GFX_WINDOW_ALIGNMENT_${INDEX}       <#noparse>${</#noparse>${GFX_WINDOW_ALIGNMENT}<#noparse>}</#noparse>
#define GFX_WINDOW_SCHEME_${INDEX}          <#noparse>${</#noparse>${GFX_WINDOW_SCHEME}<#noparse>}</#noparse>
</#macro>

<#macro GFX_HGC_WINDOW_ID_DEF ID VALUE>
#define <#noparse>${</#noparse>${ID}<#noparse>}</#noparse>                  ${VALUE} 
</#macro>

<#macro GFX_HGC_WINDOW_EXTERN_DEF ID>
    GFX_GOL_WINDOW* p<#noparse>${</#noparse>${ID}<#noparse>}</#noparse>Obj;
</#macro>

<#macro GFX_HGC_PICTURE_DEF INDEX GFX_PICTURE_LEFT GFX_PICTURE_TOP GFX_PICTURE_RIGHT GFX_PICTURE_BOTTOM GFX_PICTURE_STATE GFX_PICTURE_SCALE GFX_PICTURE_SCHEME>
#define GFX_PICTURE_LEFT_${INDEX}            <#noparse>${</#noparse>${GFX_PICTURE_LEFT}<#noparse>}</#noparse>
#define GFX_PICTURE_TOP_${INDEX}             <#noparse>${</#noparse>${GFX_PICTURE_TOP}<#noparse>}</#noparse>
#define GFX_PICTURE_RIGHT_${INDEX}           <#noparse>${</#noparse>${GFX_PICTURE_RIGHT}<#noparse>}</#noparse>
#define GFX_PICTURE_BOTTOM_${INDEX}          <#noparse>${</#noparse>${GFX_PICTURE_BOTTOM}<#noparse>}</#noparse>
#define GFX_PICTURE_STATE_${INDEX}          <#noparse>${</#noparse>${GFX_PICTURE_STATE}<#noparse>}</#noparse>
#define GFX_PICTURE_SCALE_${INDEX}       <#noparse>${</#noparse>${GFX_PICTURE_SCALE}<#noparse>}</#noparse>
#define GFX_PICTURE_SCHEME_${INDEX}          <#noparse>${</#noparse>${GFX_PICTURE_SCHEME}<#noparse>}</#noparse>
</#macro>

<#macro GFX_HGC_PICTURE_ID_DEF ID VALUE>
#define <#noparse>${</#noparse>${ID}<#noparse>}</#noparse>                  ${VALUE} 
</#macro>

<#macro GFX_HGC_PICTURE_EXTERN_DEF ID>
    GFX_GOL_PICTURECONTROL* p<#noparse>${</#noparse>${ID}<#noparse>}</#noparse>Obj;
</#macro>

<#macro GFX_HGC_LINE_ID_DEF ID VALUE>
#define <#noparse>${</#noparse>${ID}<#noparse>}</#noparse>                 ${VALUE} 
</#macro>

<#macro GFX_HGC_RECTANGLE_ID_DEF ID VALUE>
#define <#noparse>${</#noparse>${ID}<#noparse>}</#noparse>                 ${VALUE} 
</#macro>

<#macro GFX_HGC_CIRCLE_ID_DEF ID VALUE>
#define <#noparse>${</#noparse>${ID}<#noparse>}</#noparse>                 ${VALUE} 
</#macro>

<#macro GFX_HGC_IMAGE_ID_DEF ID VALUE>
#define <#noparse>${</#noparse>${ID}<#noparse>}</#noparse>                 ${VALUE} 
</#macro>

<#macro GFX_HGC_TEXT_ID_DEF ID VALUE>
#define <#noparse>${</#noparse>${ID}<#noparse>}</#noparse>                 ${VALUE} 
</#macro>

<#macro GFX_HGC_SCREEN_STATE_DEF SCR_ID>
    HGC_SCREEN_STATE_SETUP_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>,
    HGC_SCREEN_STATE_PRE_DRAW_GOL_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>,
    HGC_SCREEN_STATE_DRAW_GOL_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>,
    HGC_SCREEN_STATE_POST_DRAW_GOL_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>,
    HGC_SCREEN_STATE_PRE_DRAW_PRIMITIVE_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>,
    HGC_SCREEN_STATE_DRAW_PRIMITIVE_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>,
    HGC_SCREEN_STATE_POST_DRAW_PRIMITIVE_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>,
    HGC_SCREEN_STATE_DISPLAY_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>,
</#macro>


<#macro GFX_HGC_FIRST_SCREEN SCR_ID>
        GFX_HGC_SetScreenState(HGC_SCREEN_STATE_DRAW_GOL_SCREEN_${SCR_ID});
</#macro>

<#macro GFX_HGC_SETUP_SCREEN
			SCR_ID
			RED
			GREEN
			BLUE
			AUTOCLEAR>
        case ${SCR_ID}:
		<#if AUTOCLEAR = true>
            GFX_ColorSet(GFX_INDEX_0, GFX_RGBConvert(${RED},${GREEN},${BLUE}));
            GFX_ScreenClear(GFX_INDEX_0);
			
		</#if>
<#if CONFIG_GFX_HGC_USE_GOL = true>
            GFX_GOL_ObjectListFree(GFX_INDEX_0); // free memory for the objects in the previous linked list and start new list
</#if>
            break;
</#macro>

<#macro GFX_HGC_SCREEN_STATE_TRANSITION INDEX SCR_ID>
        case HGC_SCREEN_STATE_SETUP_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>:
<#if CONFIG_GFX_HGC_USE_GOL = true>
            GFX_HGC_SetScreenState(HGC_SCREEN_STATE_PRE_DRAW_GOL_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>);
<#else>
            GFX_HGC_SetupScreen(<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>);

            GFX_HGC_SetScreenState(HGC_SCREEN_STATE_PRE_DRAW_PRIMITIVE_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>);
</#if>
            break;
<#if CONFIG_GFX_HGC_USE_GOL = true>
        case HGC_SCREEN_STATE_PRE_DRAW_GOL_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>:
            GFX_HGC_SetScreenState(HGC_SCREEN_STATE_DRAW_GOL_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>);
            break;
        case HGC_SCREEN_STATE_DRAW_GOL_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>:
            GFX_HGC_SetupScreen(<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>);
            GFX_HGC_DrawScreen_GOL(<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>);
            GFX_HGC_SetScreenState(HGC_SCREEN_STATE_POST_DRAW_GOL_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>);
            break;
        case HGC_SCREEN_STATE_POST_DRAW_GOL_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>:
            GFX_HGC_SetScreenState(HGC_SCREEN_STATE_PRE_DRAW_PRIMITIVE_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>);
            break;
</#if>
        case HGC_SCREEN_STATE_PRE_DRAW_PRIMITIVE_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>:
            GFX_HGC_SetScreenState(HGC_SCREEN_STATE_DRAW_PRIMITIVE_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>);
            break;
        case HGC_SCREEN_STATE_DRAW_PRIMITIVE_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>:
            GFX_HGC_DrawScreen_Primitives(<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>);
            GFX_HGC_SetScreenState(HGC_SCREEN_STATE_POST_DRAW_PRIMITIVE_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>);
            break;
        case HGC_SCREEN_STATE_POST_DRAW_PRIMITIVE_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>:
            GFX_HGC_SetScreenState(HGC_SCREEN_STATE_DISPLAY_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>);
            break;
        case HGC_SCREEN_STATE_DISPLAY_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>:
            break;
</#macro>

<#macro GFX_HGC_SCREEN_DRAW_GOL SCREEN_ID SCREEN_INDEX SCREEN_NUM_ITEMS>
        case <#noparse>${</#noparse>${SCREEN_ID}<#noparse>}</#noparse>:
<#noparse><#include "/framework/gfx/templates/gfx_hgc_definitions_macros.ftl"></#noparse>
<#noparse><#assign itemList = [</#noparse>${CONFIG_GFX_HGC_SCREEN_GOL_ITEMS_LIST}<#noparse>]></#noparse>
<#noparse><@GFX_HGC_SCREEN_DRAW_LIST</#noparse>
    SCREEN_INDEX = "${SCREEN_INDEX}" items=itemList ${CONFIG_GFX_HGC_SCREEN_GOL_ITEMS_LIST_KEYS}
    <#noparse>/></#noparse>
            break;
</#macro>

<#macro GFX_HGC_SCREEN_DRAW_PRIMITIVES SCREEN_ID SCREEN_INDEX SCREEN_NUM_ITEMS>
        case <#noparse>${</#noparse>${SCREEN_ID}<#noparse>}</#noparse>:
<#noparse><#include "/framework/gfx/templates/gfx_hgc_definitions_macros.ftl"></#noparse>
<#noparse><#assign itemList = [</#noparse>${CONFIG_GFX_HGC_SCREEN_PRIMITIVE_ITEMS_LIST}<#noparse>]></#noparse>
<#noparse><@GFX_HGC_SCREEN_DRAW_LIST</#noparse>
    SCREEN_INDEX = "${SCREEN_INDEX}" items=itemList ${CONFIG_GFX_HGC_SCREEN_PRIMITIVE_ITEMS_LIST_KEYS}
    <#noparse>/></#noparse>
            break;
</#macro>

<#macro GFX_HGC_SCREEN_DRAW_LIST SCREEN_INDEX items itemList...>
    <#list items as item>
        <#list itemList?keys as itemScreen>
            <#if itemScreen == item && itemList[itemScreen]?html == SCREEN_INDEX> 
            GFX_HGC_DrawItem(${item});
            </#if>
        </#list>
    </#list>
</#macro>

<#macro GFX_HGC_SCREEN_EVENT SCR_ID>
        case HGC_SCREEN_STATE_DISPLAY_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>:
<#if CONFIG_GFX_HGC_HAS_BUTTONS = true>
            if (GFX_HGC_MsgButtons(objMsg, pObj, pMsg) == true)
                return true;
</#if>
<#if CONFIG_GFX_HGC_HAS_DGTL_MTRS = true>
            if (GFX_HGC_MsgDigitalMeters(objMsg, pObj, pMsg) == true)
                return true;
</#if>
<#if CONFIG_GFX_HGC_HAS_CHECKBOXES = true>
            if (GFX_HGC_MsgCheckBoxes(objMsg, pObj, pMsg) == true)
                return true;
</#if>
<#if CONFIG_GFX_HGC_HAS_RADIOBUTTONS = true>
            if (GFX_HGC_MsgRadioButtons(objMsg, pObj, pMsg) == true)
                return true;
</#if>
<#if CONFIG_GFX_HGC_HAS_SCROLLBARS = true>
            if (GFX_HGC_MsgScrollBars(objMsg, pObj, pMsg) == true)
                return true;
</#if>
<#if CONFIG_GFX_HGC_HAS_PROGRESSBARS = true>
            if (GFX_HGC_MsgProgressBars(objMsg, pObj, pMsg) == true)
                return true;
</#if>
<#if CONFIG_GFX_HGC_HAS_EDITBOXES = true>
            if (GFX_HGC_MsgEditBoxes(objMsg, pObj, pMsg) == true)
                return true;
</#if>
<#if CONFIG_GFX_HGC_HAS_LISTBOXES = true>
            if (GFX_HGC_MsgListBoxes(objMsg, pObj, pMsg) == true)
                return true;
</#if>
<#if CONFIG_GFX_HGC_HAS_PICTURES = true>
            if (GFX_HGC_MsgPictures(objMsg, pObj, pMsg) == true)
                return true;
</#if>
<#if CONFIG_GFX_HGC_HAS_STATICTEXTS = true>
            if (GFX_HGC_MsgStaticTexts(objMsg, pObj, pMsg) == true)
                return true;
</#if>
<#if CONFIG_GFX_HGC_HAS_WINDOWS = true>
            if (GFX_HGC_MsgWindows(objMsg, pObj, pMsg) == true)
                return true;
</#if>
<#if CONFIG_GFX_HGC_HAS_TEXTENTRYS = true>
            if (GFX_HGC_MsgTextEntrys(objMsg, pObj, pMsg) == true)
                return true;
</#if>
            break;
</#macro>

<#macro GFX_HGC_SCREEN_ID_DEF SCR_ID VALUE>
#define <#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>                 ${VALUE} 
</#macro>

<#macro GFX_HGC_CHANGE_SCREEN SCR_ID>
        case <#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>:
            GFX_HGC_SetScreenState(HGC_SCREEN_STATE_SETUP_SCREEN_<#noparse>${</#noparse>${SCR_ID}<#noparse>}</#noparse>);
            break;
</#macro>

<#macro GFX_HGC_EXTERN_RESOURCE RESOURCE>
extern const GFX_RESOURCE_HDR <#noparse>${</#noparse>${RESOURCE}<#noparse>}</#noparse>;
</#macro>

<#macro GFX_HGC_GENERATE_ACTION
			GFX_INDEX
			ACTION_ID>
<#assign text="${ACTION_ID}_NAME">
				// <#noparse>${</#noparse>${text}<#noparse>}</#noparse>
<#assign text="${ACTION_ID}_CODE">
<#noparse>${</#noparse>${text}<#noparse>}</#noparse>
</#macro>
