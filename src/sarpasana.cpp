#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <yoga/Yoga.h>
#include <sstream>
#include <vector>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

using namespace pybind11::literals;

py::str from_yg_align(YGAlign a) {
    switch(a) {
        case YGAlign::YGAlignAuto: return py::str("auto");
        case YGAlign::YGAlignFlexStart: return py::str("flex_start");
        case YGAlign::YGAlignCenter: return py::str("center");
        case YGAlign::YGAlignFlexEnd: return py::str("flex_end");
        case YGAlign::YGAlignStretch: return py::str("stretch");
        case YGAlign::YGAlignBaseline: return py::str("baseline");
        case YGAlign::YGAlignSpaceBetween: return py::str("space_between");
        case YGAlign::YGAlignSpaceAround: return py::str("space_around");
        case YGAlign::YGAlignSpaceEvenly: return py::str("space_evenly");
        default: throw std::runtime_error(std::string("unknown flavor of ygalign"));
    }
}

YGAlign to_yg_align(std::string str) {
    if (str == "auto") { return YGAlign::YGAlignAuto; }
    if (str == "flex_start") { return YGAlign::YGAlignFlexStart; }
    if (str == "center") { return YGAlign::YGAlignCenter; }
    if (str == "flex_end") { return YGAlign::YGAlignFlexEnd; }
    if (str == "stretch") { return YGAlign::YGAlignStretch; }
    if (str == "baseline") { return YGAlign::YGAlignBaseline; }
    if (str == "space_between") { return YGAlign::YGAlignSpaceBetween; }
    if (str == "space_around") { return YGAlign::YGAlignSpaceAround; }
    if (str == "space_evenly") { return YGAlign::YGAlignSpaceEvenly; }
    throw py::value_error(std::string("ygalign accepts auto|flex_start|center|flex_end|stretch|baseline|space_between|space_around|space_evenly"));
}

py::str from_yg_box_sizing(YGBoxSizing a) {
    switch(a) {
        case YGBoxSizing::YGBoxSizingBorderBox: return py::str("border_box");
        case YGBoxSizing::YGBoxSizingContentBox: return py::str("content_box");
        default: throw std::runtime_error(std::string("unknown flavor of ygbox_sizing"));
    }
}

YGBoxSizing to_yg_box_sizing(std::string str) {
    if (str == "border_box") { return YGBoxSizing::YGBoxSizingBorderBox; }
    if (str == "content_box") { return YGBoxSizing::YGBoxSizingContentBox; }
    throw py::value_error(std::string("ygbox_sizing accepts border_box|content_box"));
}

py::str from_yg_dimension(YGDimension a) {
    switch(a) {
        case YGDimension::YGDimensionWidth: return py::str("width");
        case YGDimension::YGDimensionHeight: return py::str("height");
        default: throw std::runtime_error(std::string("unknown flavor of ygdimension"));
    }
}

YGDimension to_yg_dimension(std::string str) {
    if (str == "width") { return YGDimension::YGDimensionWidth; }
    if (str == "height") { return YGDimension::YGDimensionHeight; }
    throw py::value_error(std::string("ygdimension accepts width|height"));
}

py::str from_yg_direction(YGDirection a) {
    switch(a) {
        case YGDirection::YGDirectionInherit: return py::str("inherit");
        case YGDirection::YGDirectionLTR: return py::str("ltr");
        case YGDirection::YGDirectionRTL: return py::str("rtl");
        default: throw std::runtime_error(std::string("unknown flavor of ygdirection"));
    }
}

YGDirection to_yg_direction(std::string str) {
    if (str == "inherit") { return YGDirection::YGDirectionInherit; }
    if (str == "ltr") { return YGDirection::YGDirectionLTR; }
    if (str == "rtl") { return YGDirection::YGDirectionRTL; }
    throw py::value_error(std::string("ygdirection accepts inherit|ltr|rtl"));
}

py::str from_yg_display(YGDisplay a) {
    switch(a) {
        case YGDisplay::YGDisplayFlex: return py::str("flex");
        case YGDisplay::YGDisplayNone: return py::str("none");
        case YGDisplay::YGDisplayContents: return py::str("contents");
        default: throw std::runtime_error(std::string("unknown flavor of ygdisplay"));
    }
}

YGDisplay to_yg_display(std::string str) {
    if (str == "flex") { return YGDisplay::YGDisplayFlex; }
    if (str == "none") { return YGDisplay::YGDisplayNone; }
    if (str == "contents") { return YGDisplay::YGDisplayContents; }
    throw py::value_error(std::string("ygdisplay accepts flex|none|contents"));
}
    
py::str from_yg_flex_direction(YGFlexDirection a) {
    switch(a) {
        case YGFlexDirection::YGFlexDirectionColumn: return py::str("column");
        case YGFlexDirection::YGFlexDirectionColumnReverse: return py::str("column_reverse");
        case YGFlexDirection::YGFlexDirectionRow: return py::str("row");
        case YGFlexDirection::YGFlexDirectionRowReverse: return py::str("row_reverse");
        default: throw std::runtime_error(std::string("unknown flavor of ygflex_direction"));
    }
}

YGFlexDirection to_yg_flex_direction(std::string str) {
    if (str == "column") { return YGFlexDirection::YGFlexDirectionColumn; }
    if (str == "column_reverse") { return YGFlexDirection::YGFlexDirectionColumnReverse; }
    if (str == "row") { return YGFlexDirection::YGFlexDirectionRow; }
    if (str == "row_reverse") { return YGFlexDirection::YGFlexDirectionRowReverse; }
    throw py::value_error(std::string("ygflex_direction accepts column|column_reverse|row|row_reverse"));
}

py::str from_yg_justify(YGJustify a) {
    switch(a) {
        case YGJustify::YGJustifyFlexStart: return py::str("flex_start");
        case YGJustify::YGJustifyCenter: return py::str("center");
        case YGJustify::YGJustifyFlexEnd: return py::str("flex_end");
        case YGJustify::YGJustifySpaceBetween: return py::str("space_between");
        case YGJustify::YGJustifySpaceAround: return py::str("space_around");
        case YGJustify::YGJustifySpaceEvenly: return py::str("space_evenly");
        default: throw std::runtime_error(std::string("unknown flavor of ygjustify"));
    }
}

YGJustify to_yg_justify(std::string str) {
    if (str == "flex_start") { return YGJustify::YGJustifyFlexStart; }
    if (str == "center") { return YGJustify::YGJustifyCenter; }
    if (str == "flex_end") { return YGJustify::YGJustifyFlexEnd; }
    if (str == "space_between") { return YGJustify::YGJustifySpaceBetween; }
    if (str == "space_around") { return YGJustify::YGJustifySpaceAround; }
    if (str == "space_evenly") { return YGJustify::YGJustifySpaceEvenly; }
    throw py::value_error(std::string("ygjustify accepts flex_start|center|flex_end|space_between|space_around|space_evenly"));
}

py::str from_yg_log_level(YGLogLevel a) {
    switch(a) {
        case YGLogLevel::YGLogLevelError: return py::str("error");
        case YGLogLevel::YGLogLevelWarn: return py::str("warn");
        case YGLogLevel::YGLogLevelInfo: return py::str("info");
        case YGLogLevel::YGLogLevelDebug: return py::str("debug");
        case YGLogLevel::YGLogLevelVerbose: return py::str("verbose");
        case YGLogLevel::YGLogLevelFatal: return py::str("fatal");
        default: throw std::runtime_error(std::string("unknown flavor of ygloglevel"));
    }
}

py::str from_yg_measure_mode(YGMeasureMode a) {
    switch(a) {
        case YGMeasureMode::YGMeasureModeUndefined: return py::str("undefined");
        case YGMeasureMode::YGMeasureModeExactly: return py::str("exactly");
        case YGMeasureMode::YGMeasureModeAtMost: return py::str("at_most");
        default: throw std::runtime_error(std::string("unknown flavor of ygmeasure_mode"));
    }
}

YGMeasureMode to_yg_measure_mode(std::string str) {
    if (str == "undefined") { return YGMeasureMode::YGMeasureModeUndefined; }
    if (str == "exactly") { return YGMeasureMode::YGMeasureModeExactly; }
    if (str == "at_most") { return YGMeasureMode::YGMeasureModeAtMost; }
    throw py::value_error(std::string("ygmeasure_mode accepts undefined|exactly|at_most"));
}

py::str from_yg_node_type(YGNodeType a) {
    switch(a) {
        case YGNodeType::YGNodeTypeDefault: return py::str("default");
        case YGNodeType::YGNodeTypeText: return py::str("text");
        default: throw std::runtime_error(std::string("unknown flavor of ygnode_type"));
    }
}

YGNodeType to_yg_node_type(std::string str) {
    if (str == "default") { return YGNodeType::YGNodeTypeDefault; }
    if (str == "text") { return YGNodeType::YGNodeTypeText; }
    throw py::value_error(std::string("ygnode_type accepts default|text"));
}

py::str from_yg_position_type(YGPositionType a) {
    switch(a) {
        case YGPositionType::YGPositionTypeStatic: return py::str("static");
        case YGPositionType::YGPositionTypeRelative: return py::str("relative");
        case YGPositionType::YGPositionTypeAbsolute: return py::str("absolute");
        default: throw std::runtime_error(std::string("unknown flavor of ygposition_type"));
    }
}

YGPositionType to_yg_position_type(std::string str) {
    if (str == "static") { return YGPositionType::YGPositionTypeStatic; }
    if (str == "relative") { return YGPositionType::YGPositionTypeRelative; }
    if (str == "absolute") { return YGPositionType::YGPositionTypeAbsolute; }
    throw py::value_error(std::string("ygposition_type accepts static|relative|absolute"));
}

py::str from_yg_overflow(YGOverflow a) {
    switch(a) {
        case YGOverflow::YGOverflowVisible: return py::str("visible");
        case YGOverflow::YGOverflowHidden: return py::str("hidden");
        case YGOverflow::YGOverflowScroll: return py::str("scroll");
        default: throw std::runtime_error(std::string("unknown flavor of ygoverflow"));
    }
}

YGOverflow to_yg_overflow(std::string str) {
    if (str == "visible") { return YGOverflow::YGOverflowVisible; }
    if (str == "hidden") { return YGOverflow::YGOverflowHidden; }
    if (str == "scroll") { return YGOverflow::YGOverflowScroll; }
    throw py::value_error(std::string("ygoverflow accepts visible|hidden|scroll"));
}

py::str from_yg_wrap(YGWrap a) {
    switch(a) {
        case YGWrap::YGWrapNoWrap: return py::str("no_wrap");
        case YGWrap::YGWrapWrap: return py::str("wrap");
        case YGWrap::YGWrapWrapReverse: return py::str("reverse");
        default: throw std::runtime_error(std::string("unknown flavor of ygwrap"));
    }
}

YGWrap to_yg_wrap(std::string str) {
    if (str == "no_wrap") { return YGWrap::YGWrapNoWrap; }
    if (str == "wrap") { return YGWrap::YGWrapWrap; }
    if (str == "reverse") { return YGWrap::YGWrapWrapReverse; }
    throw py::value_error(std::string("ygwrap accepts no_wrap|wrap|reverse"));
}

YGSize measure_func_callback(YGNodeConstRef node, float width, YGMeasureMode widthMode, float height, YGMeasureMode heightMode);
float baseline_func_callback(YGNodeConstRef node, float width, float height);
void dirtied_func_callback(YGNodeConstRef node);

#define MeasureFunc std::function<py::tuple(Node&, float, std::string, float, std::string)>
#define BaselineFunc std::function<float(Node&, float, float)>
#define DirtiedFunc std::function<void(Node&)>

static std::string Undefined("undefined");
static std::string Auto("auto");
static std::string MaxContent("max_content");
static std::string MinContent("min_content");
static std::string FitContent("fit_content");
static std::string Stretch("stretch");

class Percent {
public:
    float value;
    Percent(float _value) : value(_value) { }

    std::string Repr() {
        std::stringstream s;
        s << value << "*pc";
        return s.str();
    }

    Percent Mul(float other) {
        return Percent(other * value);
    }
};

py::object from_yg(YGValue yg) {
    switch (yg.unit) {
        case YGUnit::YGUnitUndefined:
            return py::cast(Undefined);
        case YGUnit::YGUnitPoint:
            return py::float_(yg.value);
        case YGUnit::YGUnitPercent:
            return py::cast(Percent(yg.value));
        case YGUnit::YGUnitAuto:
            return py::cast(Auto);
        case YGUnit::YGUnitMaxContent:
            return py::cast(MaxContent);
        case YGUnit::YGUnitFitContent:
            return py::cast(FitContent);
        case YGUnit::YGUnitStretch:
            return py::cast(&Stretch);
        default:
            throw std::runtime_error(std::string("Could not convert yg value to python"));
    }
}

class Config;

class Node {
    public:
        YGNodeRef ref;
        MeasureFunc measureFunc;
        BaselineFunc baselineFunc;
        DirtiedFunc dirtiedFunc;
        py::list children;
        py::object my_config;
        Node(Config* config);
        Node() : ref(YGNodeNew()), measureFunc(NULL), baselineFunc(NULL), dirtiedFunc(NULL) {
            YGNodeSetContext(ref, static_cast<void*>(this));
        }

        ~Node() {
            YGNodeFree(ref);
        }

        static Node* Cast(YGNodeConstRef ref) {
            if (!ref) return NULL;
            return static_cast<Node*>(YGNodeGetContext(ref));
        }

        void Reset() {
            YGNodeReset(ref);
        }

        void SetHasNewLayout(bool hasNewLayout) {
            YGNodeSetHasNewLayout(ref, hasNewLayout);
        }

        bool GetHasNewLayout() {
            return YGNodeGetHasNewLayout(ref);
        }

        bool IsDirty() {
            return YGNodeIsDirty(ref);
        }

        void MarkDirty() {
            YGNodeMarkDirty(ref);
        }

        void SetDirtiedFunc(DirtiedFunc func) {
            dirtiedFunc = func;
            if (func) YGNodeSetDirtiedFunc(ref, dirtied_func_callback);
            else      YGNodeSetDirtiedFunc(ref, NULL);
        }

        DirtiedFunc GetDirtiedFunc() {
            return dirtiedFunc;
        }

        void Append(Node& child) {
            size_t index = children.size();
            children.append(child);
            YGNodeInsertChild(ref, child.ref, index);
        }

        void Insert(size_t index, Node& child) {
            if(index < 0) throw py::index_error();
            children.insert(index, child);
            YGNodeInsertChild(ref, child.ref, index);
        }

        void Swap(size_t index, Node& child) {
            children[index] = child;
            YGNodeSwapChild(ref, child.ref, index);
        }

        void Remove(Node& child) {
            YGNodeRemoveChild(ref, child.ref);
            py::list replacement;
            for (auto that : children) {
                Node& child1 = that.cast<Node&>();
                if (&child != &child1) replacement.append(child1);
            }
            children = replacement;
        }

        void Clear() {
            children.clear();
            YGNodeRemoveAllChildren(ref);
        }

        //void SetChildren(std::vector<Node> vec) {
        //    YGNodeSetChildren(ref, vec.data, vec.size());
        //}

        Node* GetItem(size_t index) {
            YGNodeRef node = YGNodeGetChild(ref, index);
            if (node) return Node::Cast(node);
            else throw py::index_error();
        }

        size_t Length() {
            return YGNodeGetChildCount(ref);
        }

        Node* GetOwner() {
            return Node::Cast(YGNodeGetOwner(ref));
        }

        Node* GetParent() {
            return Node::Cast(YGNodeGetParent(ref));
        }

        void SetMeasureFunc(MeasureFunc func) {
            measureFunc = func;
            if (func) YGNodeSetMeasureFunc(ref, measure_func_callback);
            else      YGNodeSetMeasureFunc(ref, NULL);
        }

        MeasureFunc GetMeasureFunc() {
            return measureFunc;
        }

        bool HasMeasureFunc() {
            return YGNodeHasMeasureFunc(ref);
        }

        void SetBaselineFunc(BaselineFunc func) {
            baselineFunc = func;
            if (func) YGNodeSetBaselineFunc(ref, baseline_func_callback);
            else      YGNodeSetBaselineFunc(ref, NULL);
        }

        BaselineFunc GetBaselineFunc() {
            return baselineFunc;
        }

        bool HasBaselineFunc() {
            return YGNodeHasBaselineFunc(ref);
        }

        void SetIsReferenceBaseline(bool yes) {
            YGNodeSetIsReferenceBaseline(ref, yes);
        }

        bool GetIsReferenceBaseline() {
            return YGNodeIsReferenceBaseline(ref);
        }

        void SetAlwaysFormsContainingBlock(bool yes) {
            YGNodeSetAlwaysFormsContainingBlock(ref, yes);
        }

        bool GetAlwaysFormsContainingBlock() {
            return YGNodeGetAlwaysFormsContainingBlock(ref);
        }

        void SetConfig(Config* config);
        Config* GetConfig();
};

YGSize measure_func_callback(YGNodeConstRef node, float width, YGMeasureMode widthMode, float height, YGMeasureMode heightMode) {
    Node* _node = Node::Cast(node);
    py::tuple result = _node->measureFunc(*_node, width, from_yg_measure_mode(widthMode), height, from_yg_measure_mode(heightMode));
    return YGSize{result[0].cast<float>(), result[1].cast<float>()};
}

float baseline_func_callback(YGNodeConstRef node, float width, float height) {
    Node* _node = Node::Cast(node);
    return _node->baselineFunc(*_node, width, height);
}

void dirtied_func_callback(YGNodeConstRef node) {
    Node* _node = Node::Cast(node);
    _node->dirtiedFunc(*_node);
}

int logging_callback(YGConfigConstRef config,
                     YGNodeConstRef node,
                     YGLogLevel level,
                     const char* format,
                     va_list args);

YGNodeRef clone_node_callback(YGNodeConstRef oldNode, YGNodeConstRef owner, size_t childIndex);

#define Logger std::function<int(Config&, Node&, const std::string loglevel, const std::string message)>

class Config {
    private:
        bool own;
    public:
        Logger logger;
        YGConfigRef ref;
        Config(YGConfigConstRef ref) : ref(const_cast<YGConfigRef>(ref)), own(false), logger(NULL) { }
        Config() : ref(YGConfigNew()), own(true), logger(NULL) {
            YGConfigSetContext(ref, static_cast<void*>(this));
        }

        ~Config() {
            if (own) {
                YGConfigFree(ref);
            }
        }

        static Config* Cast(YGConfigConstRef ref) {
            if (!ref) return NULL;
            return static_cast<Config*>(YGConfigGetContext(ref));
        }

        static Config GetDefault() {
            return Config(YGConfigGetDefault());
        }

#define CHECK_OWNED if (!own) throw std::runtime_error(std::string("cannot write to default config"))

        void SetUseWebDefaults(bool enabled) {
            CHECK_OWNED;
            YGConfigSetUseWebDefaults(ref, enabled);
        }

        bool GetUseWebDefaults() {
            return YGConfigGetUseWebDefaults(ref);
        }

        void SetPointScaleFactor(float pixelsInPoint) {
            CHECK_OWNED;
            YGConfigSetPointScaleFactor(ref, pixelsInPoint);
        }

        float GetPointScaleFactor() {
            return YGConfigGetPointScaleFactor(ref);
        }

        void SetErrata(unsigned long errata) {
            CHECK_OWNED;
            YGConfigSetErrata(ref, (YGErrata)errata);
        }
        
        unsigned long GetErrata() {
            return (unsigned long)YGConfigGetErrata(ref);
        }

        void SetLogger(Logger l) {
            CHECK_OWNED;
            logger = l;
            if (l) YGConfigSetLogger(ref, logging_callback);
            else   YGConfigSetLogger(ref, NULL);
        }

        Logger GetLogger() { return logger; }

        void SetExperimentalFeatureEnabled(YGExperimentalFeature feature, bool enabled) {
            CHECK_OWNED;
            YGConfigSetExperimentalFeatureEnabled(ref, feature, enabled);
        }
        bool IsExperimentalFeatureEnabled(YGExperimentalFeature feature) {
            return YGConfigIsExperimentalFeatureEnabled(ref, feature);
        }

        // TODO
        // void SetCloneNodeFunc(CloneNodeFunc func) {
        //     CHECK_OWNED;
        //     cloneNodeFunc = func;
        //     if (func) YGConfigSetCloneNodeFunc(ref, clone_node_callback);
        //     else      YGConfigSetCloneNodeFunc(ref, NULL);
        // }
};

int logging_callback(YGConfigConstRef config,
                     YGNodeConstRef node,
                     YGLogLevel level,
                     const char* format,
                     va_list args) {
    Config* cfg = Config::Cast(config);
    Node* n = Node::Cast(node);
    std::string message;
    va_list ap_copy;
    va_copy(ap_copy, args);
    size_t len = vsnprintf(0, 0, format, ap_copy);
    message.resize(len + 1);  // need space for NUL
    vsnprintf(&message[0], len + 1, format, args);
    message.resize(len);  // remove the NUL
    return cfg->logger(*cfg, *n, from_yg_log_level(level), message);
}

YGNodeRef clone_node_callback(YGNodeConstRef oldNode, YGNodeConstRef owner, size_t childIndex) {
    return NULL;
}

Node::Node(Config* config) {
    if (config) {
        ref = YGNodeNewWithConfig(config->ref);
    } else {
        ref = YGNodeNew();
    }
    measureFunc = NULL;
    baselineFunc = NULL;
    dirtiedFunc = NULL;
    YGNodeSetContext(ref, static_cast<void*>(this));
    my_config = py::cast(*config);
}

void Node::SetConfig(Config* config) {
    YGNodeSetConfig(ref, config->ref);
    my_config = py::cast(*config);
}

Config* Node::GetConfig() {
    return Config::Cast(YGNodeGetConfig(ref));
}

class Edges {
public:
    std::vector<YGEdge> edges;
    py::list values;
    void Add(YGEdge edge, py::handle value) {
        edges.push_back(edge);
        values.append(value);
    }
    Edges(py::args args, py::kwargs kwargs) {
        if (kwargs.size() > 0 && args.size() > 0) throw py::value_error(std::string("edges expects either keywords or positional arguments, not both.")); 
        switch(args.size()) {
            case 0: {
                for (auto item : kwargs) {
                    std::string key = item.first.cast<std::string>();
                    if (key == "all") Add(YGEdge::YGEdgeAll, item.second);
                    else if (key == "vertical") Add(YGEdge::YGEdgeVertical, item.second);
                    else if (key == "horizontal") Add(YGEdge::YGEdgeHorizontal, item.second);
                    else if (key == "top") Add(YGEdge::YGEdgeTop, item.second);
                    else if (key == "right") Add(YGEdge::YGEdgeRight, item.second);
                    else if (key == "bottom") Add(YGEdge::YGEdgeBottom, item.second);
                    else if (key == "left") Add(YGEdge::YGEdgeLeft, item.second);
                    else if (key == "start") Add(YGEdge::YGEdgeStart, item.second);
                    else if (key == "end") Add(YGEdge::YGEdgeEnd, item.second);
                    else throw py::value_error(std::string("edges keyword argument must signify a key, all|vertical|horizontal|top|right|bottom|left|start|end"));
                }
                break;
            }
            case 1:
                Add(YGEdge::YGEdgeAll, args[0]);
                break;
            case 2:
                Add(YGEdge::YGEdgeVertical, args[0]);
                Add(YGEdge::YGEdgeHorizontal, args[1]);
                break;
            case 3:
                Add(YGEdge::YGEdgeTop, args[0]);
                Add(YGEdge::YGEdgeHorizontal, args[1]);
                Add(YGEdge::YGEdgeBottom, args[2]);
                break;
            case 4:
                Add(YGEdge::YGEdgeTop, args[0]);
                Add(YGEdge::YGEdgeRight, args[1]);
                Add(YGEdge::YGEdgeBottom, args[2]);
                Add(YGEdge::YGEdgeLeft, args[3]);
                break;
            default: throw py::value_error(std::string("edges understands at most 4 positional arguments"));
        }
    }
};

class EdgeProxy {
public:
    Node* node;
    YGValue (*getfn)(YGNodeConstRef, YGEdge);
    explicit EdgeProxy(Node* _node, YGValue (*_getfn)(YGNodeConstRef, YGEdge)) : node(_node), getfn(_getfn) { }
    YGValue Edge(YGEdge edge) { return getfn(node->ref, edge); }
    py::object Left() { return from_yg(Edge(YGEdge::YGEdgeLeft)); }
    py::object Top() { return from_yg(Edge(YGEdge::YGEdgeTop)); }
    py::object Right() { return from_yg(Edge(YGEdge::YGEdgeRight)); }
    py::object Bottom() { return from_yg(Edge(YGEdge::YGEdgeBottom)); }
    py::object Start() { return from_yg(Edge(YGEdge::YGEdgeStart)); }
    py::object End() { return from_yg(Edge(YGEdge::YGEdgeEnd)); }
    py::object Horizontal() { return from_yg(Edge(YGEdge::YGEdgeHorizontal)); }
    py::object Vertical() { return from_yg(Edge(YGEdge::YGEdgeVertical)); }
    py::object All() { return from_yg(Edge(YGEdge::YGEdgeAll)); }
};

class FloatEdgeProxy {
public:
    Node* node;
    float (*getfn)(YGNodeConstRef, YGEdge);
    FloatEdgeProxy(Node* _node, float (*_getfn)(YGNodeConstRef, YGEdge)) : node(_node), getfn(_getfn) { }
    float Edge(YGEdge edge) { return getfn(node->ref, edge); }
    float Left() { return Edge(YGEdge::YGEdgeLeft); }
    float Top() { return Edge(YGEdge::YGEdgeTop); }
    float Right() { return Edge(YGEdge::YGEdgeRight); }
    float Bottom() { return Edge(YGEdge::YGEdgeBottom); }
    float Start() { return Edge(YGEdge::YGEdgeStart); }
    float End() { return Edge(YGEdge::YGEdgeEnd); }
    float Horizontal() { return Edge(YGEdge::YGEdgeHorizontal); }
    float Vertical() { return Edge(YGEdge::YGEdgeVertical); }
    float All() { return Edge(YGEdge::YGEdgeAll); }
};

class Gutters {
public:
    std::vector<YGGutter> gutters;
    py::list values;
    void Add(YGGutter gutter, py::handle value) {
        gutters.push_back(gutter);
        values.append(value);
    }
    Gutters(py::args args, py::kwargs kwargs) {
        if (kwargs.size() > 0 && args.size() > 0) throw py::value_error(std::string("gutters expects either keywords or positional arguments, not both.")); 
        switch(args.size()) {
            case 0: {
                for (auto item : kwargs) {
                    std::string key = item.first.cast<std::string>();
                    if (key == "all") Add(YGGutter::YGGutterAll, item.second);
                    else if (key == "column") Add(YGGutter::YGGutterColumn, item.second);
                    else if (key == "row") Add(YGGutter::YGGutterRow, item.second);
                    else throw py::value_error(std::string("gutters keyword argument must signify a key, all|row|column"));
                }
                break;
            }
            case 1:
                Add(YGGutter::YGGutterAll, args[0]);
                break;
            case 2:
                Add(YGGutter::YGGutterColumn, args[0]);
                Add(YGGutter::YGGutterRow, args[1]);
                break;
            default: throw py::value_error(std::string("gutters understands at most 2 positional arguments"));
        }
    }
};

class GutterProxy {
public:
    Node* node;
    GutterProxy(Node* _node) : node(_node) { }
    py::object Column() { return from_yg(YGNodeStyleGetGap(node->ref, YGGutter::YGGutterColumn)); }
    py::object Row() { return from_yg(YGNodeStyleGetGap(node->ref, YGGutter::YGGutterRow)); }
    py::object All() { return from_yg(YGNodeStyleGetGap(node->ref, YGGutter::YGGutterAll)); }
};

PYBIND11_MODULE(sarpasana, m) {
    m.doc() = R"pbdoc(
        sarpasana
        ---------
        
        Bindings for the yoga layout library
    )pbdoc";

    m.attr("ErrataStretchFlexBasis") = (unsigned long)YGErrataStretchFlexBasis;
    m.attr("ErrataAbsolutePositionWithoutInsetsExludesPadding") = (unsigned long)YGErrataAbsolutePositionWithoutInsetsExcludesPadding;
    m.attr("ErrataAbsolutePositionPercentAgainstInnerSize") = (unsigned long)YGErrataAbsolutePercentAgainstInnerSize;
    m.attr("ErrataAll") = (unsigned long)YGErrataAll;
    m.attr("ErrataClassic") = (unsigned long)YGErrataClassic;

    // TODO: chalk one of these away once in a while.
    py::enum_<YGExperimentalFeature>(m, "ExperimentalFeature")
        .value("WebFlexBasis", YGExperimentalFeature::YGExperimentalFeatureWebFlexBasis);

    py::class_<Config>(m, "Config")
        .def(py::init<>())
        .def_property("use_web_defaults", &Config::GetUseWebDefaults, &Config::SetUseWebDefaults)
        .def_static("get_default", &Config::GetDefault)
        .def_property("errata", &Config::GetErrata, &Config::SetErrata)
        .def_property("logger", &Config::GetLogger, &Config::SetLogger)
        .def("set_experimental_feature_enabled", &Config::SetExperimentalFeatureEnabled)
        .def("is_experimental_feature_enabled", &Config::IsExperimentalFeatureEnabled);

    py::class_<Node>(m, "Node")
        .def(py::init<Config*>(), "config"_a = static_cast<Config*>(nullptr))
        .def("reset", &Node::Reset)
        .def("calculate_layout", [](Node& node, float aw, float ah, std::string od) { YGNodeCalculateLayout(node.ref, aw, ah, to_yg_direction(od)); })
        .def_property("has_new_layout", &Node::GetHasNewLayout, &Node::SetHasNewLayout)
        .def_property_readonly("dirty", &Node::IsDirty)
        .def("mark_dirty", &Node::MarkDirty)
        .def_property("dirtied_func", &Node::GetDirtiedFunc, &Node::SetDirtiedFunc)
        .def("append", &Node::Append)
        .def("insert", &Node::Insert)
        .def("swap", &Node::Swap)
        .def("remove", &Node::Remove)
        .def("clear", &Node::Clear)
        .def("__getitem__", &Node::GetItem)
        .def("__len__", &Node::Length)
        .def_property_readonly("owner", &Node::GetOwner)
        .def_property_readonly("parent", &Node::GetParent)
        .def_property("measure_func", &Node::GetMeasureFunc, &Node::SetMeasureFunc)
        .def("has_measure_func", &Node::HasMeasureFunc)
        .def_property("baseline_func", &Node::GetBaselineFunc, &Node::SetBaselineFunc)
        .def("has_baseline_func", &Node::HasBaselineFunc)
        .def_property("is_reference_baseline", &Node::GetIsReferenceBaseline, &Node::SetIsReferenceBaseline)
        .def_property("node_type", [](Node& self) { return from_yg_node_type(YGNodeGetNodeType(self.ref)); },
                                   [](Node& self, std::string param) { YGNodeSetNodeType(self.ref, to_yg_node_type(param)); })
        .def_property("always_forms_containing_block", &Node::GetAlwaysFormsContainingBlock, &Node::SetAlwaysFormsContainingBlock)
        .def_property("config", &Node::GetConfig, &Node::SetConfig)
        .def_property_readonly("left", [](Node& node) { return YGNodeLayoutGetLeft(node.ref); })
        .def_property_readonly("top", [](Node& node) { return YGNodeLayoutGetTop(node.ref); })
        .def_property_readonly("right", [](Node& node) { return YGNodeLayoutGetRight(node.ref); })
        .def_property_readonly("bottom", [](Node& node) { return YGNodeLayoutGetBottom(node.ref); })
        .def_property_readonly("width", [](Node& node) { return YGNodeLayoutGetWidth(node.ref); })
        .def_property_readonly("height", [](Node& node) { return YGNodeLayoutGetHeight(node.ref); })
        .def_property_readonly("direction", [](Node& node) { return from_yg_direction(YGNodeLayoutGetDirection(node.ref)); })
        .def_property_readonly("had_overflow", [](Node& node) { return YGNodeLayoutGetHadOverflow(node.ref); })
        .def_property_readonly("margin", [](Node& self) { return FloatEdgeProxy(&self, YGNodeLayoutGetMargin); })
        .def_property_readonly("border", [](Node& self) { return FloatEdgeProxy(&self, YGNodeLayoutGetBorder); })
        .def_property_readonly("padding", [](Node& self) { return FloatEdgeProxy(&self, YGNodeLayoutGetPadding); }) 
        .def("copy_style", [](Node& dst, Node& src) { YGNodeCopyStyle(dst.ref, src.ref); })
        .def_property("style_direction",
            [](Node &self) { return from_yg_direction(YGNodeStyleGetDirection(self.ref)); },
            [](Node &self, std::string direction) { YGNodeStyleSetDirection(self.ref, to_yg_direction(direction)); })
        .def_property("style_flex_direction",
            [](Node &self) { return from_yg_flex_direction(YGNodeStyleGetFlexDirection(self.ref)); },
            [](Node &self, std::string param) { YGNodeStyleSetFlexDirection(self.ref, to_yg_flex_direction(param)); })
        .def_property("style_justify_content",
            [](Node &self) { return from_yg_justify(YGNodeStyleGetJustifyContent(self.ref)); },
            [](Node &self, std::string param) { YGNodeStyleSetJustifyContent(self.ref, to_yg_justify(param)); })
        .def_property("style_align_content",
            [](Node &self) { return from_yg_align(YGNodeStyleGetAlignContent(self.ref)); },
            [](Node &self, std::string param) { YGNodeStyleSetAlignContent(self.ref, to_yg_align(param)); })
        .def_property("style_align_items",
            [](Node &self) { return from_yg_align(YGNodeStyleGetAlignItems(self.ref)); },
            [](Node &self, std::string param) { YGNodeStyleSetAlignItems(self.ref, to_yg_align(param)); })
        .def_property("style_align_self",
            [](Node &self) { return from_yg_align(YGNodeStyleGetAlignSelf(self.ref)); },
            [](Node &self, std::string param) { YGNodeStyleSetAlignSelf(self.ref, to_yg_align(param)); })
        .def_property("style_position_type",
            [](Node &self) { return from_yg_position_type(YGNodeStyleGetPositionType(self.ref)); },
            [](Node &self, std::string param) { YGNodeStyleSetPositionType(self.ref, to_yg_position_type(param)); })
        .def_property("style_flex_wrap",
            [](Node &self) { return from_yg_wrap(YGNodeStyleGetFlexWrap(self.ref)); },
            [](Node &self, std::string param) { YGNodeStyleSetFlexWrap(self.ref, to_yg_wrap(param)); })
        .def_property("style_overflow",
            [](Node &self) { return from_yg_overflow(YGNodeStyleGetOverflow(self.ref)); },
            [](Node &self, std::string param) { YGNodeStyleSetOverflow(self.ref, to_yg_overflow(param)); })
        .def_property("style_display",
            [](Node &self) { return from_yg_display(YGNodeStyleGetDisplay(self.ref)); },
            [](Node &self, std::string param) { YGNodeStyleSetDisplay(self.ref, to_yg_display(param)); })
        .def_property("style_flex",
            [](Node &self) { return YGNodeStyleGetFlex(self.ref); },
            [](Node &self, float param) { YGNodeStyleSetFlex(self.ref, param); })
        .def_property("style_flex_grow",
            [](Node &self) { return YGNodeStyleGetFlexGrow(self.ref); },
            [](Node &self, float param) { YGNodeStyleSetFlexGrow(self.ref, param); })
        .def_property("style_flex_shrink",
            [](Node &self) { return YGNodeStyleGetFlexShrink(self.ref); },
            [](Node &self, float param) { YGNodeStyleSetFlexShrink(self.ref, param); })
        .def_property("style_flex_basis",
            [](Node &self) { return from_yg(YGNodeStyleGetFlexBasis(self.ref)); },
            [](Node &self, py::object param) {
                if (py::isinstance<py::float_>(param)) {
                    float value = param.cast<float>();
                    YGNodeStyleSetFlexBasis(self.ref, value);
                } else if (py::isinstance<py::str>(param)) {
                    std::string gv = param.cast<std::string>();
                    if (gv == "auto") { YGNodeStyleSetFlexBasisAuto(self.ref); }
                    else if (gv == "max_content") { YGNodeStyleSetFlexBasisMaxContent(self.ref); }
                    else if (gv == "fit_content") { YGNodeStyleSetFlexBasisFitContent(self.ref); }
                    else if (gv == "stretch") { YGNodeStyleSetFlexBasisStretch(self.ref); }
                    else { throw std::runtime_error(std::string("style_flex_basis should be one of float|pc|auto|max_content|fit_content|stretch")); }
                } else {
                    Percent* gv = param.cast<Percent*>();
                    YGNodeStyleSetFlexBasisPercent(self.ref, gv->value);
                }
            })
        .def_property("style_height",
            [](Node &self) { return from_yg(YGNodeStyleGetHeight(self.ref)); },
            [](Node &self, py::object param) {
                if (py::isinstance<py::float_>(param)) {
                    float value = param.cast<float>();
                    YGNodeStyleSetHeight(self.ref, value);
                } else if (py::isinstance<py::str>(param)) {
                    std::string gv = param.cast<std::string>();
                    if (gv == "auto") { YGNodeStyleSetHeightAuto(self.ref); }
                    else if (gv == "max_content") { YGNodeStyleSetHeightMaxContent(self.ref); }
                    else if (gv == "fit_content") { YGNodeStyleSetHeightFitContent(self.ref); }
                    else if (gv == "stretch") { YGNodeStyleSetHeightStretch(self.ref); }
                    else { throw std::runtime_error(std::string("style_height should be one of float|pc|auto|max_content|fit_content|stretch")); }
                } else {
                    Percent* gv = param.cast<Percent*>();
                    YGNodeStyleSetHeightPercent(self.ref, gv->value);
                }
            })
        .def_property("style_min_height",
            [](Node &self) { return from_yg(YGNodeStyleGetMinHeight(self.ref)); },
            [](Node &self, py::object param) {
                if (py::isinstance<py::float_>(param)) {
                    float value = param.cast<float>();
                    YGNodeStyleSetMinHeight(self.ref, value);
                } else if (py::isinstance<py::str>(param)) {
                    std::string gv = param.cast<std::string>();
                    if (gv == "max_content") { YGNodeStyleSetMinHeightMaxContent(self.ref); }
                    else if (gv == "fit_content") { YGNodeStyleSetMinHeightFitContent(self.ref); }
                    else if (gv == "stretch") { YGNodeStyleSetMinHeightStretch(self.ref); }
                    else { throw std::runtime_error(std::string("style_min_height should be one of float|pc|max_content|fit_content|stretch")); }
                } else {
                    Percent* gv = param.cast<Percent*>();
                    YGNodeStyleSetMinHeightPercent(self.ref, gv->value);
                }
            })
        .def_property("style_width",
            [](Node &self) { return from_yg(YGNodeStyleGetWidth(self.ref)); },
            [](Node &self, py::object param) {
                if (py::isinstance<py::float_>(param)) {
                    float value = param.cast<float>();
                    YGNodeStyleSetWidth(self.ref, value);
                } else if (py::isinstance<py::str>(param)) {
                    std::string gv = param.cast<std::string>();
                    if (gv == "auto") { YGNodeStyleSetWidthAuto(self.ref); }
                    else if (gv == "max_content") { YGNodeStyleSetWidthMaxContent(self.ref); }
                    else if (gv == "fit_content") { YGNodeStyleSetWidthFitContent(self.ref); }
                    else if (gv == "stretch") { YGNodeStyleSetWidthStretch(self.ref); }
                    else { throw std::runtime_error(std::string("style_width should be one of float|pc|auto|max_content|fit_content|stretch")); }
                } else {
                    Percent* gv = param.cast<Percent*>();
                    YGNodeStyleSetWidthPercent(self.ref, gv->value);
                }
            })
        .def_property("style_min_width",
            [](Node &self) { return from_yg(YGNodeStyleGetMinWidth(self.ref)); },
            [](Node &self, py::object param) {
                if (py::isinstance<py::float_>(param)) {
                    float value = param.cast<float>();
                    YGNodeStyleSetMinWidth(self.ref, value);
                } else if (py::isinstance<py::str>(param)) {
                    std::string gv = param.cast<std::string>();
                    if (gv == "max_content") { YGNodeStyleSetMinWidthMaxContent(self.ref); }
                    else if (gv == "fit_content") { YGNodeStyleSetMinWidthFitContent(self.ref); }
                    else if (gv == "stretch") { YGNodeStyleSetMinWidthStretch(self.ref); }
                    else { throw std::runtime_error(std::string("style_min_width should be one of float|pc|max_content|fit_content|stretch")); }
                } else {
                    Percent* gv = param.cast<Percent*>();
                    YGNodeStyleSetMinWidthPercent(self.ref, gv->value);
                }
            })
        .def_property("style_max_width",
            [](Node &self) { return from_yg(YGNodeStyleGetMaxHeight(self.ref)); },
            [](Node &self, py::object param) {
                if (py::isinstance<py::float_>(param)) {
                    float value = param.cast<float>();
                    YGNodeStyleSetMaxWidth(self.ref, value);
                } else if (py::isinstance<py::str>(param)) {
                    std::string gv = param.cast<std::string>();
                    if (gv == "max_content") { YGNodeStyleSetMaxWidthMaxContent(self.ref); }
                    else if (gv == "fit_content") { YGNodeStyleSetMaxWidthFitContent(self.ref); }
                    else if (gv == "stretch") { YGNodeStyleSetMaxWidthStretch(self.ref); }
                    else { throw std::runtime_error(std::string("style_max_width should be one of float|pc|max_content|fit_content|stretch")); }
                } else {
                    Percent* gv = param.cast<Percent*>();
                    YGNodeStyleSetMaxWidthPercent(self.ref, gv->value);
                }
            })
        .def_property("style_max_height",
            [](Node &self) { return from_yg(YGNodeStyleGetMaxWidth(self.ref)); },
            [](Node &self, py::object param) {
                if (py::isinstance<py::float_>(param)) {
                    float value = param.cast<float>();
                    YGNodeStyleSetMaxHeight(self.ref, value);
                } else if (py::isinstance<py::str>(param)) {
                    std::string gv = param.cast<std::string>();
                    if (gv == "max_content") { YGNodeStyleSetMaxHeightMaxContent(self.ref); }
                    else if (gv == "fit_content") { YGNodeStyleSetMaxHeightFitContent(self.ref); }
                    else if (gv == "stretch") { YGNodeStyleSetMaxHeightStretch(self.ref); }
                    else { throw std::runtime_error(std::string("style_max_heigth should be one of float|pc|max_content|fit_content|stretch")); }
                } else {
                    Percent* gv = param.cast<Percent*>();
                    YGNodeStyleSetMaxHeightPercent(self.ref, gv->value);
                }
            })
        .def_property("style_box_sizing",
            [](Node &self) { return from_yg_box_sizing(YGNodeStyleGetBoxSizing(self.ref)); },
            [](Node &self, std::string param) { YGNodeStyleSetBoxSizing(self.ref, to_yg_box_sizing(param)); })
        .def_property("style_aspect_ratio",
            [](Node &self) { return YGNodeStyleGetAspectRatio(self.ref); },
            [](Node &self, float param) { YGNodeStyleSetAspectRatio(self.ref, param); })
        .def_property("style_margin",
            [](Node &self) { return EdgeProxy(&self, YGNodeStyleGetMargin); },
            [](Node &self, Edges &edges) {
                size_t sz = edges.values.size();
                for (size_t i = 0; i < sz; ++i) {
                    YGEdge     edge  = edges.edges[i];
                    py::handle param = edges.values[i];
                    if (py::isinstance<py::float_>(param)) {
                        float value = param.cast<float>();
                        YGNodeStyleSetMargin(self.ref, edge, value);
                    } else if (py::isinstance<py::str>(param)) {
                        std::string gv = param.cast<std::string>();
                        if (gv == "auto") { YGNodeStyleSetMarginAuto(self.ref, edge); }
                        else { throw std::runtime_error(std::string("style_margin should be one of float|pc|auto")); }
                    } else {
                        Percent* gv = param.cast<Percent*>();
                        YGNodeStyleSetMarginPercent(self.ref, edge, gv->value);
                    }
                }
            })
        .def_property("style_border",
            [](Node &self) { return FloatEdgeProxy(&self, YGNodeStyleGetBorder); },
            [](Node &self, Edges &edges) {
                size_t sz = edges.values.size();
                for (size_t i = 0; i < sz; ++i) {
                    YGEdge     edge  = edges.edges[i];
                    py::handle param = edges.values[i];
                    float value = param.cast<float>();
                    YGNodeStyleSetBorder(self.ref, edge, value);
                }
            })
        .def_property("style_position",
            [](Node &self) { return EdgeProxy(&self, YGNodeStyleGetPosition); },
            [](Node &self, Edges &edges) {
                size_t sz = edges.values.size();
                for (size_t i = 0; i < sz; ++i) {
                    YGEdge     edge  = edges.edges[i];
                    py::handle param = edges.values[i];
                    if (py::isinstance<py::float_>(param)) {
                        float value = param.cast<float>();
                        YGNodeStyleSetPosition(self.ref, edge, value);
                    } else if (py::isinstance<py::str>(param)) {
                        std::string gv = param.cast<std::string>();
                        if (gv == "auto") { YGNodeStyleSetPositionAuto(self.ref, edge); }
                        else { throw std::runtime_error(std::string("style_position should be one of float|pc|auto")); }
                    } else {
                        Percent* gv = param.cast<Percent*>();
                        YGNodeStyleSetPositionPercent(self.ref, edge, gv->value);
                    }
                }
            })
        .def_property("style_padding",
            [](Node &self) { return EdgeProxy(&self, YGNodeStyleGetPadding); },
            [](Node &self, Edges &edges) {
                size_t sz = edges.values.size();
                for (size_t i = 0; i < sz; ++i) {
                    YGEdge     edge  = edges.edges[i];
                    py::handle param = edges.values[i];
                    if (py::isinstance<py::float_>(param)) {
                        float value = param.cast<float>();
                        YGNodeStyleSetPadding(self.ref, edge, value);
                    } else {
                        Percent* gv = param.cast<Percent*>();
                        YGNodeStyleSetPaddingPercent(self.ref, edge, gv->value);
                    }
                }
            })
        .def_property("style_gap",
            [](Node &self) { return GutterProxy(&self); },
            [](Node &self, Gutters &gutters) {
                size_t sz = gutters.values.size();
                for (size_t i = 0; i < sz; ++i) {
                    YGGutter   gutter = gutters.gutters[i];
                    py::handle param  = gutters.values[i];
                    if (py::isinstance<py::float_>(param)) {
                        float value = param.cast<float>();
                        YGNodeStyleSetGap(self.ref, gutter, value);
                    } else {
                        Percent* gv = param.cast<Percent*>();
                        YGNodeStyleSetGapPercent(self.ref, gutter, gv->value);
                    }
                }
            });

    m.def("round_value_to_pixel_grid", &YGRoundValueToPixelGrid,
          "value"_a,
          "pointScaleFactor"_a,
          "forceCeil"_a,
          "forceFloow"_a);

    py::class_<Percent>(m, "Percent")
        .def(py::init<float>())
        .def_readonly("value", &Percent::value)
        .def("__repr__", &Percent::Repr)
        .def("__mul__", &Percent::Mul)
        .def("__rmul__", &Percent::Mul);

    m.attr("pc") = Percent(1.0f);

    py::class_<Edges>(m, "edges")
        .def(py::init<py::args, py::kwargs>());

    py::class_<Gutters>(m, "gutters")
        .def(py::init<py::args, py::kwargs>());

    py::class_<FloatEdgeProxy>(m, "FloatEdgeProxy")
        .def_property_readonly("left", &FloatEdgeProxy::Left)
        .def_property_readonly("top", &FloatEdgeProxy::Top)
        .def_property_readonly("right", &FloatEdgeProxy::Right)
        .def_property_readonly("bottom", &FloatEdgeProxy::Bottom)
        .def_property_readonly("start", &FloatEdgeProxy::Start)
        .def_property_readonly("end", &FloatEdgeProxy::End)
        .def_property_readonly("horizontal", &FloatEdgeProxy::Horizontal)
        .def_property_readonly("vertical", &FloatEdgeProxy::Vertical)
        .def_property_readonly("all", &FloatEdgeProxy::All);

    py::class_<EdgeProxy>(m, "EdgeProxy")
        .def_property_readonly("left", &EdgeProxy::Left)
        .def_property_readonly("top", &EdgeProxy::Top)
        .def_property_readonly("right", &EdgeProxy::Right)
        .def_property_readonly("bottom", &EdgeProxy::Bottom)
        .def_property_readonly("start", &EdgeProxy::Start)
        .def_property_readonly("end", &EdgeProxy::End)
        .def_property_readonly("horizontal", &EdgeProxy::Horizontal)
        .def_property_readonly("vertical", &EdgeProxy::Vertical)
        .def_property_readonly("all", &EdgeProxy::All);

    py::class_<GutterProxy>(m, "GutterProxy")
        .def_property_readonly("column", &GutterProxy::Column)
        .def_property_readonly("row", &GutterProxy::Row)
        .def_property_readonly("all", &GutterProxy::All);

    m.def("float_is_undefined", &YGFloatIsUndefined, "value"_a);

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
