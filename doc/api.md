# Sarpasana API docs

## Config

    config = Config()
    config = Config.get_default()

It comes with following fields and methods:

    .use_web_defaults : bool
    .errata : int
    .logger : (node : Node, loglevel : str, message : str) -> int
    .set_experimental_feature_enabled(feature, enabled)
    .is_experimental_feature_enabled(feature) : bool

valid loglevel strings:

    error warn info debug verbose fatal

## Edges and gutters

`edges` allows following forms:

    edges(all)
    edges(vertical, horizontal)
    edges(top, horizontal, bottom)
    edges(top, right, bottom, left)

Additionally edges can be called with keyword arguments,
following arguments are accepted:

    all vertical horizontal top right bottom left start end

`EdgeProxy` -objects returned from API provide the same argument
names as attributes.

`gutters` allos following forms:

    gutters(all)
    gutters(column, row)

And it can be called with following keyword arguments:

    all row column

Likewise, `GutterProxy` -objects respond to these arguments as attributes.

## Node

    node = Node(config = None : Config)

There are following methods and fields:

    .reset()
    .calculate_layout(
        avail_width : float,
        avail_height : float, 
        owner_direction : str [inherit | ltr | rtl])
    .has_new_layout : bool
    .dirty : bool (read only)
    .mark_dirty()
    .dirtied_func : (this : Node) -> None
    .append()
    .insert(index : int, node : Node)
    .swap(index : int, node : Node)
    .remove(node : Node)
    .clear()

    node[index : int] : Node
    len(node) : int

    .owner : Node (read only)
    .parent : Node (read only)
    .measure_func : (this : Node,
                     width : float,
                     width_mode : str [undefined | exactly | at_most],
                     height : float,
                     height_mode : str [undefined | exactly | at_most])
    .has_measure_func() : bool
    .has_baseline_func() : bool
    .is_reference_baseline : bool
    .node_type : str [default | text]
    .always_forms_containing_block : bool
    .config : Config
    .left : float (read only)
    .top : float (read only)
    .right : float (read only)
    .bottom : float (read only)
    .width : float (read only)
    .height : float (read only)
    .direction : str [inherit | ltr | rtl] (read only)
    .had_overflow : bool (read only)
    .margin : EdgeProxy (read only)
    .border : FloatEdgeProxy (read only)
    .padding : EdgeProxy (read only)
    .copy_style(src : Node)
    .style_direction : str [inherit | ltr | rtl]
    .style_flex_direction : str [column | column_reverse | row | row_reverse]
    .style_justify_content : str
        [ auto | flex_start | center | flex_end
        | stretch | baseline | space_between
        | space_around | space_evenly]
    .style_align_content : str
        [ auto | flex_start | center | flex_end
        | stretch | baseline | space_between
        | space_around | space_evenly ]
    .style_align_items : str
        [ auto | flex_start | center | flex_end
        | stretch | baseline | space_between
        | space_around | space_evenly ]
    .style_align_self : str
        [ auto | flex_start | center | flex_end
        | stretch | baseline | space_between
        | space_around | space_evenly ]
    .style_position_type : str
        [ static | relative | absolute ]
    .style_flex_wrap : str
        [ no_wrap | wrap | reverse ]
    .style_overflow : str
        [ visible | hidden | scroll ]
    .style_display : str
        [ flex | none | contents ]
    .style_flex : float
    .style_flex : float
    .style_flex_shrink : float
    .style_flex_basis : float | x*pc | auto | max_content | fit_content | stretch
    .style_width : float | x*pc | auto | max_content | fit_content | stretch
    .style_min_width : float | x*pc | max_content | fit_content | stretch
    .style_max_width : float | x*pc | max_content | fit_content | stretch
    .style_height : float | x*pc | auto | max_content | fit_content | stretch
    .style_min_height : float | x*pc | max_content | fit_content | stretch
    .style_max_height : float | x*pc | max_content | fit_content | stretch
    .style_box_sizing : str
        [ border_box | content_box ]
    .style_aspect_ratio : float
    .style_margin : Edges <--> EdgeProxy (float|x*pc|auto)
    .style_border : Edges <--> FloatEdgeProxy
    .style_position : Edges <--> EdgeProxy (float|x*pc|auto)
    .style_padding : Edges <--> EdgeProxy (float|x*pc)
    .style_gap : Gutters <--> GutterProxy (float|x*pc)

## Miscellaneous

    round_value_to_pixel_grid(value : float,
                              pt_scale_factor : float,
                              force_ceil : bool
                              force_flow : bool) : float
    pc : Percent
    float_is_undefined(value : float) : bool
