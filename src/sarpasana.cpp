#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <yoga/Yoga.h>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

using namespace pybind11::literals;

YGSize measure_func_callback(YGNodeConstRef node, float width, YGMeasureMode widthMode, float height, YGMeasureMode heightMode);
float baseline_func_callback(YGNodeConstRef node, float width, float height);
void dirtied_func_callback(YGNodeConstRef node);

#define MeasureFunc std::function<py::tuple(Node&, float, YGMeasureMode, float, YGMeasureMode)>
#define BaselineFunc std::function<float(Node&, float, float)>
#define DirtiedFunc std::function<void(Node&)>

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

        void CalculateLayout(float availableWidth, float availableHeight, YGDirection ownerDirection) {
            YGNodeCalculateLayout(ref, availableWidth, availableHeight, ownerDirection);
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

        void SetNodeType(YGNodeType nodeType) {
            YGNodeSetNodeType(ref, nodeType);
        }

        YGNodeType GetNodeType() {
            return YGNodeGetNodeType(ref);
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
    py::tuple result = _node->measureFunc(*_node, width, widthMode, height, heightMode);
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

#define Logger std::function<int(Config&, Node&, YGLogLevel, const std::string message)>

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
    return cfg->logger(*cfg, *n, level, message);
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

PYBIND11_MODULE(sarpasana, m) {
    m.doc() = R"pbdoc(
        sarpasana
        ---------
        
        Bindings for the yoga layout library
    )pbdoc";

    py::enum_<YGAlign>(m, "Align")
      .value("Auto", YGAlign::YGAlignAuto)
      .value("FlexStart", YGAlign::YGAlignFlexStart)
      .value("Center", YGAlign::YGAlignCenter)
      .value("FlexEnd", YGAlign::YGAlignFlexEnd)
      .value("Stretch", YGAlign::YGAlignStretch)
      .value("Baseline", YGAlign::YGAlignBaseline)
      .value("SpaceBetween", YGAlign::YGAlignSpaceBetween)
      .value("SpaceAround", YGAlign::YGAlignSpaceAround)
      .value("SpaceEvenly", YGAlign::YGAlignSpaceEvenly);

    py::enum_<YGBoxSizing>(m, "BoxSizing")
      .value("BorderBox", YGBoxSizing::YGBoxSizingBorderBox)
      .value("ContentBox", YGBoxSizing::YGBoxSizingContentBox);

    py::enum_<YGDimension>(m, "Dimension")
        .value("Width", YGDimension::YGDimensionWidth)
        .value("Height", YGDimension::YGDimensionHeight);

    py::enum_<YGDirection>(m, "Direction")
        .value("Inherit", YGDirection::YGDirectionInherit)
        .value("LTR", YGDirection::YGDirectionLTR)
        .value("RTL", YGDirection::YGDirectionRTL);

    py::enum_<YGDisplay>(m, "Display")
        .value("Flex", YGDisplay::YGDisplayFlex)
        .value("No", YGDisplay::YGDisplayNone)
        .value("Contents", YGDisplay::YGDisplayContents);

    py::enum_<YGEdge>(m, "Edge")
        .value("Left", YGEdge::YGEdgeLeft)
        .value("Top", YGEdge::YGEdgeTop)
        .value("Right", YGEdge::YGEdgeRight)
        .value("Bottom", YGEdge::YGEdgeBottom)
        .value("Start", YGEdge::YGEdgeStart)
        .value("End", YGEdge::YGEdgeEnd)
        .value("Horizontal", YGEdge::YGEdgeHorizontal)
        .value("Vertical", YGEdge::YGEdgeVertical)
        .value("All", YGEdge::YGEdgeAll);

    m.attr("ErrataStretchFlexBasis") = (unsigned long)YGErrataStretchFlexBasis;
    m.attr("ErrataAbsolutePositionWithoutInsetsExludesPadding") = (unsigned long)YGErrataAbsolutePositionWithoutInsetsExcludesPadding;
    m.attr("ErrataAbsolutePositionPercentAgainstInnerSize") = (unsigned long)YGErrataAbsolutePercentAgainstInnerSize;
    m.attr("ErrataAll") = (unsigned long)YGErrataAll;
    m.attr("ErrataClassic") = (unsigned long)YGErrataClassic;

    py::enum_<YGExperimentalFeature>(m, "ExperimentalFeature")
        .value("WebFlexBasis", YGExperimentalFeature::YGExperimentalFeatureWebFlexBasis);
    
    py::enum_<YGFlexDirection>(m, "FlexDirection")
        .value("Column", YGFlexDirection::YGFlexDirectionColumn)
        .value("ColumnReverse", YGFlexDirection::YGFlexDirectionColumnReverse)
        .value("Row", YGFlexDirection::YGFlexDirectionRow)
        .value("RowReverse", YGFlexDirection::YGFlexDirectionRowReverse);

    py::enum_<YGGutter>(m, "Gutter")
        .value("Column", YGGutter::YGGutterColumn)
        .value("Row", YGGutter::YGGutterRow)
        .value("All", YGGutter::YGGutterAll);

    py::enum_<YGJustify>(m, "Justify")
        .value("FlexStart", YGJustify::YGJustifyFlexStart)
        .value("Center", YGJustify::YGJustifyCenter)
        .value("FlexEnd", YGJustify::YGJustifyFlexEnd)
        .value("SpaceBetween", YGJustify::YGJustifySpaceBetween)
        .value("SpaceAround", YGJustify::YGJustifySpaceAround)
        .value("SpaceEvenly", YGJustify::YGJustifySpaceEvenly);

    py::enum_<YGLogLevel>(m, "LogLevel")
        .value("Error", YGLogLevel::YGLogLevelError)
        .value("Warn", YGLogLevel::YGLogLevelWarn)
        .value("Info", YGLogLevel::YGLogLevelInfo)
        .value("Debug", YGLogLevel::YGLogLevelDebug)
        .value("Verbose", YGLogLevel::YGLogLevelVerbose)
        .value("Fatal", YGLogLevel::YGLogLevelFatal);

    py::enum_<YGMeasureMode>(m, "MeasureMode")
        .value("Undefined", YGMeasureMode::YGMeasureModeUndefined)
        .value("Exactly", YGMeasureMode::YGMeasureModeExactly)
        .value("AtMost", YGMeasureMode::YGMeasureModeAtMost);

    py::enum_<YGNodeType>(m, "NodeType")
        .value("Default", YGNodeType::YGNodeTypeDefault)
        .value("Text", YGNodeType::YGNodeTypeText);

    py::enum_<YGOverflow>(m, "Overflow")
        .value("Visible", YGOverflow::YGOverflowVisible)
        .value("Hidden", YGOverflow::YGOverflowHidden)
        .value("Scroll", YGOverflow::YGOverflowScroll);

    py::enum_<YGPositionType>(m, "PositionType")
        .value("Static", YGPositionType::YGPositionTypeStatic)
        .value("Relative", YGPositionType::YGPositionTypeRelative)
        .value("Absolute", YGPositionType::YGPositionTypeAbsolute);

    py::enum_<YGUnit>(m, "Unit")
        .value("Undefined", YGUnit::YGUnitUndefined)
        .value("Point", YGUnit::YGUnitPoint)
        .value("Percent", YGUnit::YGUnitPercent)
        .value("Auto", YGUnit::YGUnitAuto)
        .value("MaxContent", YGUnit::YGUnitMaxContent)
        .value("FitContent", YGUnit::YGUnitFitContent)
        .value("Stretch", YGUnit::YGUnitStretch);

    py::enum_<YGWrap>(m, "Wrap")
        .value("No", YGWrap::YGWrapNoWrap)
        .value("Yes", YGWrap::YGWrapWrap)
        .value("Reverse", YGWrap::YGWrapWrapReverse);

    m.attr("Undefined") = YGUndefined;

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
        .def("calculate_layout", &Node::CalculateLayout)
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
        .def_property("node_type", &Node::GetNodeType, &Node::SetNodeType)
        .def_property("always_forms_containing_block", &Node::GetAlwaysFormsContainingBlock, &Node::SetAlwaysFormsContainingBlock)
        .def_property("config", &Node::GetConfig, &Node::SetConfig)
        .def_property_readonly("left", [](Node& node) { return YGNodeLayoutGetLeft(node.ref); })
        .def_property_readonly("top", [](Node& node) { return YGNodeLayoutGetTop(node.ref); })
        .def_property_readonly("right", [](Node& node) { return YGNodeLayoutGetRight(node.ref); })
        .def_property_readonly("bottom", [](Node& node) { return YGNodeLayoutGetBottom(node.ref); })
        .def_property_readonly("width", [](Node& node) { return YGNodeLayoutGetWidth(node.ref); })
        .def_property_readonly("height", [](Node& node) { return YGNodeLayoutGetHeight(node.ref); })
        .def_property_readonly("direction", [](Node& node) { return YGNodeLayoutGetDirection(node.ref); })
        .def_property_readonly("had_overflow", [](Node& node) { return YGNodeLayoutGetHadOverflow(node.ref); })
        .def("get_margin", [](Node& node, YGEdge edge) { return YGNodeLayoutGetMargin(node.ref, edge); })
        .def("get_border", [](Node& node, YGEdge edge) { return YGNodeLayoutGetBorder(node.ref, edge); })
        .def("get_padding", [](Node& node, YGEdge edge) { return YGNodeLayoutGetPadding(node.ref, edge); })
        .def("copy_style", [](Node& dst, Node& src) { YGNodeCopyStyle(dst.ref, src.ref); })
        .def_property("style_direction",
            [](Node &self) { return YGNodeStyleGetDirection(self.ref); },
            [](Node &self, YGDirection direction) { YGNodeStyleSetDirection(self.ref, direction); })
        .def_property("style_flex_direction",
            [](Node &self) { return YGNodeStyleGetFlexDirection(self.ref); },
            [](Node &self, YGFlexDirection param) { YGNodeStyleSetFlexDirection(self.ref, param); })
        .def_property("style_justify_content",
            [](Node &self) { return YGNodeStyleGetJustifyContent(self.ref); },
            [](Node &self, YGJustify param) { YGNodeStyleSetJustifyContent(self.ref, param); })
        .def_property("style_align_content",
            [](Node &self) { return YGNodeStyleGetAlignContent(self.ref); },
            [](Node &self, YGAlign param) { YGNodeStyleSetAlignContent(self.ref, param); })
        .def_property("style_align_items",
            [](Node &self) { return YGNodeStyleGetAlignItems(self.ref); },
            [](Node &self, YGAlign param) { YGNodeStyleSetAlignItems(self.ref, param); })
        .def_property("style_align_self",
            [](Node &self) { return YGNodeStyleGetAlignSelf(self.ref); },
            [](Node &self, YGAlign param) { YGNodeStyleSetAlignSelf(self.ref, param); })
        .def_property("style_position_type",
            [](Node &self) { return YGNodeStyleGetPositionType(self.ref); },
            [](Node &self, YGPositionType param) { YGNodeStyleSetPositionType(self.ref, param); })
        .def_property("style_flex_wrap",
            [](Node &self) { return YGNodeStyleGetFlexWrap(self.ref); },
            [](Node &self, YGWrap param) { YGNodeStyleSetFlexWrap(self.ref, param); })
        .def_property("style_overflow",
            [](Node &self) { return YGNodeStyleGetOverflow(self.ref); },
            [](Node &self, YGOverflow param) { YGNodeStyleSetOverflow(self.ref, param); })
        .def_property("style_display",
            [](Node &self) { return YGNodeStyleGetDisplay(self.ref); },
            [](Node &self, YGDisplay param) { YGNodeStyleSetDisplay(self.ref, param); })
        .def_property("style_flex",
            [](Node &self) { return YGNodeStyleGetFlex(self.ref); },
            [](Node &self, float param) { YGNodeStyleSetFlex(self.ref, param); })
        .def_property("style_flex_grow",
            [](Node &self) { return YGNodeStyleGetFlexGrow(self.ref); },
            [](Node &self, float param) { YGNodeStyleSetFlexGrow(self.ref, param); })
        .def_property("style_flex_shrink",
            [](Node &self) { return YGNodeStyleGetFlexShrink(self.ref); },
            [](Node &self, float param) { YGNodeStyleSetFlexShrink(self.ref, param); })
        .def("style_set_flex_basis",
            [](Node &self, float param) { YGNodeStyleSetFlexBasis(self.ref, param); })
        .def("style_set_flex_basis_percent",
            [](Node &self, float param) { YGNodeStyleSetFlexBasisPercent(self.ref, param); })
        .def("style_set_flex_basis_auto",
            [](Node &self) { YGNodeStyleSetFlexBasisAuto(self.ref); })
        .def("style_set_flex_basis_max_content",
            [](Node &self) { YGNodeStyleSetFlexBasisMaxContent(self.ref); })
        .def("style_set_flex_basis_fit_content",
            [](Node &self) { YGNodeStyleSetFlexBasisFitContent(self.ref); })
        .def("style_set_flex_basis_stretch",
            [](Node &self) { YGNodeStyleSetFlexBasisStretch(self.ref); })
        .def_property_readonly("style_flex_basis",
            [](Node &self) { return YGNodeStyleGetFlexBasis(self.ref); })
        .def("style_set_position",
            [](Node &self, YGEdge edge, float param) { YGNodeStyleSetPosition(self.ref, edge, param); })
        .def("style_set_position_percent",
            [](Node &self, YGEdge edge, float param) { YGNodeStyleSetPositionPercent(self.ref, edge, param); })
        .def("style_get_position",
            [](Node &self, YGEdge edge) { return YGNodeStyleGetPosition(self.ref, edge); })
        .def("style_set_position_auto",
            [](Node &self, YGEdge edge) { YGNodeStyleSetPositionAuto(self.ref, edge); })
        .def("style_set_margin",
            [](Node &self, YGEdge edge, float param) { YGNodeStyleSetMargin(self.ref, edge, param); })
        .def("style_set_margin_percent",
            [](Node &self, YGEdge edge, float param) { YGNodeStyleSetMarginPercent(self.ref, edge, param); })
        .def("style_get_margin",
            [](Node &self, YGEdge edge) { return YGNodeStyleGetMargin(self.ref, edge); })
        .def("style_set_margin_auto",
            [](Node &self, YGEdge edge) { YGNodeStyleSetMarginAuto(self.ref, edge); })
        .def("style_set_padding",
            [](Node &self, YGEdge edge, float param) { YGNodeStyleSetPadding(self.ref, edge, param); })
        .def("style_set_padding_percent",
            [](Node &self, YGEdge edge, float param) { YGNodeStyleSetPaddingPercent(self.ref, edge, param); })
        .def("style_get_padding",
            [](Node &self, YGEdge edge) { return YGNodeStyleGetPadding(self.ref, edge); })
        .def("style_set_border",
            [](Node &self, YGEdge edge, float param) { YGNodeStyleSetBorder(self.ref, edge, param); })
        .def("style_get_border",
            [](Node &self, YGEdge edge) { return YGNodeStyleGetBorder(self.ref, edge); })
        .def("style_set_gap",
            [](Node &self, YGGutter gutter, float param) { YGNodeStyleSetGap(self.ref, gutter, param); })
        .def("style_set_gap_percent",
            [](Node &self, YGGutter gutter, float param) { YGNodeStyleSetGapPercent(self.ref, gutter, param); })
        .def("style_get_gap",
            [](Node &self, YGGutter gutter) { return YGNodeStyleGetGap(self.ref, gutter); })
        .def_property("style_box_sizing",
            [](Node &self) { return YGNodeStyleGetBoxSizing(self.ref); },
            [](Node &self, YGBoxSizing param) { YGNodeStyleSetBoxSizing(self.ref, param); })
        .def("style_set_width",
            [](Node &self, float param) { YGNodeStyleSetWidth(self.ref, param); })
        .def("style_set_width_percent",
            [](Node &self, float param) { YGNodeStyleSetWidthPercent(self.ref, param); })
        .def_property_readonly("style_width",
            [](Node &self) { return YGNodeStyleGetWidth(self.ref); })
        .def("style_set_width_auto",
            [](Node &self) { YGNodeStyleSetWidthAuto(self.ref); })
        .def("style_set_width_max_content",
            [](Node &self) { YGNodeStyleSetWidthMaxContent(self.ref); })
        .def("style_set_width_fit_content",
            [](Node &self) { YGNodeStyleSetWidthFitContent(self.ref); })
        .def("style_set_width_stretch",
            [](Node &self) { YGNodeStyleSetWidthStretch(self.ref); })
        .def("style_set_height",
            [](Node &self, float param) { YGNodeStyleSetHeight(self.ref, param); })
        .def("style_set_height_percent",
            [](Node &self, float param) { YGNodeStyleSetHeightPercent(self.ref, param); })
        .def_property_readonly("style_height",
            [](Node &self) { return YGNodeStyleGetHeight(self.ref); })
        .def("style_set_height_auto",
            [](Node &self) { YGNodeStyleSetHeightAuto(self.ref); })
        .def("style_set_height_max_content",
            [](Node &self) { YGNodeStyleSetHeightMaxContent(self.ref); })
        .def("style_set_height_fit_content",
            [](Node &self) { YGNodeStyleSetHeightFitContent(self.ref); })
        .def("style_set_height_stretch",
            [](Node &self) { YGNodeStyleSetHeightStretch(self.ref); })
        .def("style_set_min_height",
            [](Node &self, float param) { YGNodeStyleSetMinHeight(self.ref, param); })
        .def("style_set_min_height_percent",
            [](Node &self, float param) { YGNodeStyleSetMinHeightPercent(self.ref, param); })
        .def_property_readonly("style_min_height",
            [](Node &self) { return YGNodeStyleGetMinHeight(self.ref); })
        .def("style_set_min_height_max_content",
            [](Node &self) { YGNodeStyleSetMinHeightMaxContent(self.ref); })
        .def("style_set_min_height_fit_content",
            [](Node &self) { YGNodeStyleSetMinHeightFitContent(self.ref); })
        .def("style_set_min_height_stretch",
            [](Node &self) { YGNodeStyleSetMinHeightStretch(self.ref); })
        .def("style_set_min_width",
            [](Node &self, float param) { YGNodeStyleSetMinWidth(self.ref, param); })
        .def("style_set_min_width_percent",
            [](Node &self, float param) { YGNodeStyleSetMinWidthPercent(self.ref, param); })
        .def_property_readonly("style_min_width",
            [](Node &self) { return YGNodeStyleGetMinWidth(self.ref); })
        .def("style_set_min_width_max_content",
            [](Node &self) { YGNodeStyleSetMinWidthMaxContent(self.ref); })
        .def("style_set_min_width_fit_content",
            [](Node &self) { YGNodeStyleSetMinWidthFitContent(self.ref); })
        .def("style_set_min_width_stretch",
            [](Node &self) { YGNodeStyleSetMinWidthStretch(self.ref); })
        .def("style_set_max_width",
            [](Node &self, float param) { YGNodeStyleSetMaxWidth(self.ref, param); })
        .def("style_set_max_width_percent",
            [](Node &self, float param) { YGNodeStyleSetMaxWidthPercent(self.ref, param); })
        .def_property_readonly("style_max_width",
            [](Node &self) { return YGNodeStyleGetMaxWidth(self.ref); })
        .def("style_set_max_width_max_content",
            [](Node &self) { YGNodeStyleSetMaxWidthMaxContent(self.ref); })
        .def("style_set_max_width_fit_content",
            [](Node &self) { YGNodeStyleSetMaxWidthFitContent(self.ref); })
        .def("style_set_max_width_stretch",
            [](Node &self) { YGNodeStyleSetMaxWidthStretch(self.ref); })
        .def("style_set_max_height",
            [](Node &self, float param) { YGNodeStyleSetMaxHeight(self.ref, param); })
        .def("style_set_max_height_percent",
            [](Node &self, float param) { YGNodeStyleSetMaxHeightPercent(self.ref, param); })
        .def_property_readonly("style_max_height",
            [](Node &self) { return YGNodeStyleGetMaxHeight(self.ref); })
        .def("style_set_max_height_max_content",
            [](Node &self) { YGNodeStyleSetMaxHeightMaxContent(self.ref); })
        .def("style_set_max_height_fit_content",
            [](Node &self) { YGNodeStyleSetMaxHeightFitContent(self.ref); })
        .def("style_set_max_height_stretch",
            [](Node &self) { YGNodeStyleSetMaxHeightStretch(self.ref); })
        .def_property("style_aspect_ratio",
            [](Node &self) { return YGNodeStyleGetAspectRatio(self.ref); },
            [](Node &self, float param) { YGNodeStyleSetAspectRatio(self.ref, param); });

    m.def("round_value_to_pixel_grid", &YGRoundValueToPixelGrid,
          "value"_a,
          "pointScaleFactor"_a,
          "forceCeil"_a,
          "forceFloow"_a);

    py::class_<YGValue>(m, "Value")
        .def(py::init<float, YGUnit>())
        .def_readwrite("value", &YGValue::value)
        .def_readwrite("unit", &YGValue::unit);

    m.attr("ValueAuto") = YGValueAuto;
    m.attr("ValueUndefined") = YGValueUndefined;
    m.attr("ValueZero") = YGValueZero;

    m.def("float_is_undefined", &YGFloatIsUndefined, "value"_a);

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
