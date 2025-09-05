#include "duilib_c/duilib_c.h"
#include <iostream>
#include <cassert>

// Test function prototypes
void test_horizontal_layout();
void test_tab_layout();
void test_tile_layout();  
void test_child_layout();
void test_layout_factory();

int main() {
    std::cout << "Testing Layout Module 1:1 API Mapping...\n" << std::endl;
    
    try {
        // Test layout factory
        std::cout << "Testing layout factory..." << std::endl;
        test_layout_factory();
        std::cout << "✓ Layout factory test passed\n" << std::endl;
        
        // Test HorizontalLayout  
        std::cout << "Testing HorizontalLayout..." << std::endl;
        test_horizontal_layout();
        std::cout << "✓ HorizontalLayout test passed\n" << std::endl;
        
        // Test TabLayout
        std::cout << "Testing TabLayout..." << std::endl;
        test_tab_layout();
        std::cout << "✓ TabLayout test passed\n" << std::endl;
        
        // Test TileLayout
        std::cout << "Testing TileLayout..." << std::endl;
        test_tile_layout();
        std::cout << "✓ TileLayout test passed\n" << std::endl;
        
        // Test ChildLayout
        std::cout << "Testing ChildLayout..." << std::endl;
        test_child_layout();
        std::cout << "✓ ChildLayout test passed\n" << std::endl;
        
        std::cout << "All Layout Module tests passed! ✓" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

void test_layout_factory() {
    // Test creating layouts through factory
    duilib_control_t vlayout = duilib_create_layout_by_class("VerticalLayout");
    assert(vlayout != nullptr);
    
    duilib_control_t hlayout = duilib_create_layout_by_class("HorizontalLayout");
    assert(hlayout != nullptr);
    
    duilib_control_t tablayout = duilib_create_layout_by_class("TabLayout");
    assert(tablayout != nullptr);
    
    duilib_control_t tilelayout = duilib_create_layout_by_class("TileLayout");
    assert(tilelayout != nullptr);
    
    duilib_control_t childlayout = duilib_create_layout_by_class("ChildLayout");
    assert(childlayout != nullptr);
    
    // Test layout type detection
    assert(duilib_get_layout_type(vlayout) == DUILIB_LAYOUT_TYPE_VERTICAL);
    assert(duilib_get_layout_type(hlayout) == DUILIB_LAYOUT_TYPE_HORIZONTAL);
    assert(duilib_get_layout_type(tablayout) == DUILIB_LAYOUT_TYPE_TAB);
    assert(duilib_get_layout_type(tilelayout) == DUILIB_LAYOUT_TYPE_TILE);
    assert(duilib_get_layout_type(childlayout) == DUILIB_LAYOUT_TYPE_CHILD);
    
    std::cout << "  - Layout factory creation: ✓" << std::endl;
    std::cout << "  - Layout type detection: ✓" << std::endl;
}

void test_horizontal_layout() {
    // Test creating HorizontalLayout
    duilib_horizontallayout_t hlayout = duilib_horizontallayout_create();
    assert(hlayout != nullptr);
    assert(duilib_horizontallayout_is_valid(hlayout));
    
    // Test class name
    const char* class_name = duilib_horizontallayout_get_class(hlayout);
    assert(class_name != nullptr);
    std::cout << "  - Class name: " << class_name << std::endl;
    
    // Test separator width (specific to HorizontalLayout)
    assert(duilib_horizontallayout_set_sep_width(hlayout, 5) == DUILIB_RESULT_OK);
    assert(duilib_horizontallayout_get_sep_width(hlayout) == 5);
    
    // Test separator immediate mode
    assert(duilib_horizontallayout_set_sep_imm_mode(hlayout, true) == DUILIB_RESULT_OK);
    assert(duilib_horizontallayout_is_sep_imm_mode(hlayout) == true);
    
    // Test type conversions
    duilib_container_t container = duilib_horizontallayout_to_container(hlayout);
    assert(container != nullptr);
    
    duilib_control_t control = duilib_horizontallayout_to_control(hlayout);
    assert(control != nullptr);
    
    // Test container properties
    duilib_rect_t inset = {5, 5, 5, 5};
    assert(duilib_horizontallayout_set_inset(hlayout, inset) == DUILIB_RESULT_OK);
    duilib_rect_t result_inset = duilib_horizontallayout_get_inset(hlayout);
    assert(result_inset.left == 5 && result_inset.top == 5);
    
    assert(duilib_horizontallayout_set_child_padding(hlayout, 10) == DUILIB_RESULT_OK);
    assert(duilib_horizontallayout_get_child_padding(hlayout) == 10);
    
    // Test position setting
    duilib_rect_t pos = {0, 0, 100, 50};
    assert(duilib_horizontallayout_set_pos(hlayout, pos, true) == DUILIB_RESULT_OK);
    
    // Test control count (should be 0 initially)
    assert(duilib_horizontallayout_get_count(hlayout) == 0);
    
    // Test scrollbar configuration
    assert(duilib_horizontallayout_enable_scrollbar(hlayout, false, true) == DUILIB_RESULT_OK);
    
    std::cout << "  - Separator width: ✓" << std::endl;
    std::cout << "  - Type conversions: ✓" << std::endl;
    std::cout << "  - Container properties: ✓" << std::endl;
    
    // Clean up
    duilib_horizontallayout_destroy(hlayout);
}

void test_tab_layout() {
    // Test creating TabLayout
    duilib_tablayout_t tablayout = duilib_tablayout_create();
    assert(tablayout != nullptr);
    assert(duilib_tablayout_is_valid(tablayout));
    
    // Test class name
    const char* class_name = duilib_tablayout_get_class(tablayout);
    assert(class_name != nullptr);
    std::cout << "  - Class name: " << class_name << std::endl;
    
    // Test tab selection (specific to TabLayout)
    assert(duilib_tablayout_get_cur_sel(tablayout) == -1); // No selection initially
    
    // Test type conversions
    duilib_container_t container = duilib_tablayout_to_container(tablayout);
    assert(container != nullptr);
    
    duilib_control_t control = duilib_tablayout_to_control(tablayout);
    assert(control != nullptr);
    
    // Test container properties
    assert(duilib_tablayout_set_child_padding(tablayout, 8) == DUILIB_RESULT_OK);
    assert(duilib_tablayout_get_child_padding(tablayout) == 8);
    
    // Test mouse settings
    assert(duilib_tablayout_set_mouse_enabled(tablayout, true) == DUILIB_RESULT_OK);
    assert(duilib_tablayout_is_mouse_enabled(tablayout) == true);
    
    assert(duilib_tablayout_set_mouse_child_enabled(tablayout, false) == DUILIB_RESULT_OK);
    assert(duilib_tablayout_is_mouse_child_enabled(tablayout) == false);
    
    // Test visibility
    assert(duilib_tablayout_set_visible(tablayout, false) == DUILIB_RESULT_OK);
    assert(duilib_tablayout_is_visible(tablayout) == false);
    
    assert(duilib_tablayout_set_enabled(tablayout, true) == DUILIB_RESULT_OK);
    assert(duilib_tablayout_is_enabled(tablayout) == true);
    
    // Test scroll position
    duilib_size_t scroll_pos = {0, 0};
    assert(duilib_tablayout_set_scroll_pos(tablayout, scroll_pos) == DUILIB_RESULT_OK);
    duilib_size_t result_pos = duilib_tablayout_get_scroll_pos(tablayout);
    assert(result_pos.width == 0 && result_pos.height == 0);
    
    std::cout << "  - Tab selection: ✓" << std::endl;
    std::cout << "  - Mouse and visibility: ✓" << std::endl;
    std::cout << "  - Scroll position: ✓" << std::endl;
    
    // Clean up
    duilib_tablayout_destroy(tablayout);
}

void test_tile_layout() {
    // Test creating TileLayout
    duilib_tilelayout_t tilelayout = duilib_tilelayout_create();
    assert(tilelayout != nullptr);
    assert(duilib_tilelayout_is_valid(tilelayout));
    
    // Test class name
    const char* class_name = duilib_tilelayout_get_class(tilelayout);
    assert(class_name != nullptr);
    std::cout << "  - Class name: " << class_name << std::endl;
    
    // Test fixed columns (specific to TileLayout)
    assert(duilib_tilelayout_set_fixed_columns(tilelayout, 3) == DUILIB_RESULT_OK);
    assert(duilib_tilelayout_get_fixed_columns(tilelayout) == 3);
    
    // Test child vertical padding (specific to TileLayout)
    assert(duilib_tilelayout_set_child_vpadding(tilelayout, 12) == DUILIB_RESULT_OK);
    assert(duilib_tilelayout_get_child_vpadding(tilelayout) == 12);
    
    // Test item size (specific to TileLayout)
    duilib_size_t item_size = {64, 64};
    assert(duilib_tilelayout_set_item_size(tilelayout, item_size) == DUILIB_RESULT_OK);
    duilib_size_t result_size = duilib_tilelayout_get_item_size(tilelayout);
    assert(result_size.width == 64 && result_size.height == 64);
    
    // Test grid information (specific to TileLayout)
    int columns = duilib_tilelayout_get_columns(tilelayout);
    int rows = duilib_tilelayout_get_rows(tilelayout);
    assert(columns >= 0 && rows >= 0);
    std::cout << "  - Grid info: " << columns << " columns, " << rows << " rows" << std::endl;
    
    // Test type conversions
    duilib_container_t container = duilib_tilelayout_to_container(tilelayout);
    assert(container != nullptr);
    
    duilib_control_t control = duilib_tilelayout_to_control(tilelayout);
    assert(control != nullptr);
    
    // Test container properties  
    assert(duilib_tilelayout_set_child_align(tilelayout, DT_CENTER) == DUILIB_RESULT_OK);
    assert(duilib_tilelayout_get_child_align(tilelayout) == DT_CENTER);
    
    assert(duilib_tilelayout_set_child_valign(tilelayout, DT_VCENTER) == DUILIB_RESULT_OK);
    assert(duilib_tilelayout_get_child_valign(tilelayout) == DT_VCENTER);
    
    // Test position setting
    duilib_rect_t pos = {0, 0, 200, 200};
    assert(duilib_tilelayout_set_pos(tilelayout, pos, true) == DUILIB_RESULT_OK);
    
    std::cout << "  - Fixed columns: ✓" << std::endl;
    std::cout << "  - Item size: ✓" << std::endl;
    std::cout << "  - Child padding: ✓" << std::endl;
    
    // Clean up
    duilib_tilelayout_destroy(tilelayout);
}

void test_child_layout() {
    // Test creating ChildLayout
    duilib_childlayout_t childlayout = duilib_childlayout_create();
    assert(childlayout != nullptr);
    assert(duilib_childlayout_is_valid(childlayout));
    
    // Test class name
    const char* class_name = duilib_childlayout_get_class(childlayout);
    assert(class_name != nullptr);
    std::cout << "  - Class name: " << class_name << std::endl;
    
    // Test XML layout (specific to ChildLayout)
    const char* test_xml = "<Window><Control name=\"test\" /></Window>";
    assert(duilib_childlayout_set_child_layout_xml(childlayout, test_xml) == DUILIB_RESULT_OK);
    
    const char* result_xml = duilib_childlayout_get_child_layout_xml(childlayout);
    assert(result_xml != nullptr);
    std::cout << "  - XML: " << result_xml << std::endl;
    
    // Test initialization
    assert(duilib_childlayout_init(childlayout) == DUILIB_RESULT_OK);
    
    // Test type conversions
    duilib_container_t container = duilib_childlayout_to_container(childlayout);
    assert(container != nullptr);
    
    duilib_control_t control = duilib_childlayout_to_control(childlayout);
    assert(control != nullptr);
    
    // Test container properties
    duilib_rect_t inset = {3, 3, 3, 3};
    assert(duilib_childlayout_set_inset(childlayout, inset) == DUILIB_RESULT_OK);
    duilib_rect_t result_inset = duilib_childlayout_get_inset(childlayout);
    assert(result_inset.left == 3 && result_inset.top == 3);
    
    // Test mouse settings
    assert(duilib_childlayout_set_mouse_child_enabled(childlayout, true) == DUILIB_RESULT_OK);
    assert(duilib_childlayout_is_mouse_child_enabled(childlayout) == true);
    
    // Test position
    duilib_rect_t pos = {10, 10, 110, 110};
    assert(duilib_childlayout_set_pos(childlayout, pos, false) == DUILIB_RESULT_OK);
    duilib_rect_t result_pos = duilib_childlayout_get_pos(childlayout);
    assert(result_pos.left == 10 && result_pos.top == 10);
    
    // Test find selectable (should work even with no children)
    int selectable = duilib_childlayout_find_selectable(childlayout, 0, true);
    assert(selectable == -1); // No selectable items
    
    std::cout << "  - XML layout: ✓" << std::endl;
    std::cout << "  - Initialization: ✓" << std::endl;
    std::cout << "  - Position management: ✓" << std::endl;
    
    // Clean up
    duilib_childlayout_destroy(childlayout);
}