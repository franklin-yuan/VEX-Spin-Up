#include "main.h"

lv_obj_t *label;
lv_obj_t *btnRedAuton = lv_btn_create(lv_scr_act(), NULL);
lv_obj_t *btnBlueAuton = lv_btn_create(lv_scr_act(), NULL);
lv_obj_t *btnRoller = lv_btn_create(lv_scr_act(), NULL);
lv_obj_t *btnDoubleRoller = lv_btn_create(lv_scr_act(), NULL);
lv_obj_t *btnEverything = lv_btn_create(lv_scr_act(), NULL);
lv_obj_t *cont = lv_cont_create(lv_scr_act(), NULL);
lv_obj_t *cb = lv_cb_create(cont, NULL);
bool autonEnabled = true;
bool Hard = true;
bool redAlliance = true;
uint8_t rollerDifficulty = 1;

static lv_res_t autonAlliance(lv_obj_t *btn) {
    uint8_t id = lv_obj_get_free_num(btn);
    if (id == 1) {
        lv_btn_set_state(btnRedAuton, LV_BTN_STATE_TGL_REL);
        lv_btn_set_state(btnBlueAuton, LV_BTN_STATE_REL);
        redAlliance = true;
    } else if (id == 2) {
        lv_btn_set_state(btnBlueAuton, LV_BTN_STATE_TGL_REL);
        lv_btn_set_state(btnRedAuton, LV_BTN_STATE_REL);
        redAlliance = false;
    }
    return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t autonDifficulty(lv_obj_t *btn) {
    uint8_t id = lv_obj_get_free_num(btn);
    if (id == 3) {
        lv_btn_set_state(btnRoller, LV_BTN_STATE_TGL_REL);
        lv_btn_set_state(btnDoubleRoller, LV_BTN_STATE_REL);
        lv_btn_set_state(btnEverything, LV_BTN_STATE_REL);
        rollerDifficulty = 1;
    } else if (id == 4) {
        lv_btn_set_state(btnRoller, LV_BTN_STATE_REL);
        lv_btn_set_state(btnDoubleRoller, LV_BTN_STATE_TGL_REL);
        lv_btn_set_state(btnEverything, LV_BTN_STATE_REL);
        rollerDifficulty = 2;
    } else if (id == 5) {
        lv_btn_set_state(btnRoller, LV_BTN_STATE_REL);
        lv_btn_set_state(btnDoubleRoller, LV_BTN_STATE_REL);
        lv_btn_set_state(btnEverything, LV_BTN_STATE_TGL_REL);
        rollerDifficulty = 3;
    }
    return LV_RES_OK;
}

static lv_res_t enableAuton(lv_obj_t *cb) {
    autonEnabled = lv_cb_is_checked(cb);
    printf("%s state: %d\n", lv_cb_get_text(cb), lv_cb_is_checked(cb));
    return LV_RES_OK;
}

static lv_res_t enableHardRoller(lv_obj_t *cb) {
    Hard = lv_cb_is_checked(cb);
    printf("%s state: %d\n", lv_cb_get_text(cb), lv_cb_is_checked(cb));
    return LV_RES_OK;
}

void drawAutonSelector() {
    label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label, "Autonomous Selection");
    lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 5, 15);

    label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label, "Alliance Selection");
    lv_obj_align(label, NULL, LV_ALIGN_IN_LEFT_MID, 15, -60);

    label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label, "Difficulty Selection");
    lv_obj_align(label, NULL, LV_ALIGN_IN_RIGHT_MID, -125, -60);

    lv_obj_align(btnRedAuton, NULL, LV_ALIGN_IN_LEFT_MID, 25, 20);
    lv_obj_set_free_num(btnRedAuton, 1); /*Set a unique number for the button*/
    lv_btn_set_action(btnRedAuton, LV_BTN_ACTION_CLICK, autonAlliance);
    lv_obj_set_size(btnRedAuton, LV_HOR_RES / 4, LV_VER_RES / 6);
    lv_btn_set_state(btnRedAuton, LV_BTN_STATE_TGL_REL); /*Set toggled state*/

    label = lv_label_create(btnRedAuton, NULL);
    lv_label_set_text(label, "RED");

    lv_obj_align(btnBlueAuton, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 25, 10);
    lv_btn_set_action(btnBlueAuton, LV_BTN_ACTION_CLICK, autonAlliance);
    lv_obj_set_size(btnBlueAuton, LV_HOR_RES / 4, LV_VER_RES / 6);
    lv_btn_set_state(btnBlueAuton, LV_BTN_STATE_REL); /*Set toggled state*/
    lv_obj_set_free_num(btnBlueAuton, 2);             /*Set a unique number for the button*/

    label = lv_label_create(btnBlueAuton, NULL);
    lv_label_set_text(label, "BLUE");

    //--------------------------------------------------------------------------------------------------------------
    lv_obj_align(btnRoller, NULL, LV_ALIGN_IN_RIGHT_MID, -155, 0);
    lv_obj_set_free_num(btnRoller, 3); /*Set a unique number for the button*/
    lv_btn_set_action(btnRoller, LV_BTN_ACTION_CLICK, autonDifficulty);
    lv_obj_set_size(btnRoller, LV_HOR_RES / 3, LV_VER_RES / 6);
    lv_btn_set_state(btnRoller, LV_BTN_STATE_TGL_REL); /*Set toggled state*/

    label = lv_label_create(btnRoller, NULL);
    lv_label_set_text(label, "ROLLER");

    lv_obj_align(btnDoubleRoller, NULL, LV_ALIGN_IN_RIGHT_MID, -155, 55);
    lv_obj_set_free_num(btnDoubleRoller, 4); /*Set a unique number for the button*/
    lv_btn_set_action(btnDoubleRoller, LV_BTN_ACTION_CLICK, autonDifficulty);
    lv_obj_set_size(btnDoubleRoller, LV_HOR_RES / 3, LV_VER_RES / 6);
    lv_btn_set_state(btnDoubleRoller, LV_BTN_STATE_REL); /*Set toggled state*/

    label = lv_label_create(btnDoubleRoller, NULL);
    lv_label_set_text(label, "DOUBLE");

    lv_obj_align(btnEverything, NULL, LV_ALIGN_IN_RIGHT_MID, -155, 110);
    lv_obj_set_free_num(btnEverything, 5); /*Set a unique number for the button*/
    lv_btn_set_action(btnEverything, LV_BTN_ACTION_CLICK, autonDifficulty);
    lv_obj_set_size(btnEverything, LV_HOR_RES / 3, LV_VER_RES / 6);
    lv_btn_set_state(btnEverything, LV_BTN_STATE_REL); /*Set toggled state*/

    label = lv_label_create(btnEverything, NULL);
    lv_label_set_text(label, "EVERYTHING");
    //--------------------------------------------------------------------------------------------------------------

    label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label, "Enabled");
    lv_obj_align(label, NULL, LV_ALIGN_IN_RIGHT_MID, -20, -60);

    label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label, "Hard");
    lv_obj_align(label, NULL, LV_ALIGN_IN_RIGHT_MID, -32, 30);

    /********************************************
     * Create a container for the check boxes
     ********************************************/

    /*Create  border style*/
    static lv_style_t style_border;
    lv_style_copy(&style_border, &lv_style_pretty_color);
    style_border.glass = 1;
    style_border.body.empty = 1;

    /*Create a container*/
    lv_cont_set_layout(cont, LV_LAYOUT_COL_L); /*Arrange the children in a column*/
    lv_cont_set_fit(cont, true, true);         /*Fit the size to the content*/
    lv_obj_set_style(cont, &style_border);

    /*Create check box*/
    lv_cb_set_text(cb, "");
    lv_cb_set_action(cb, enableAuton);

    lv_cb_set_checked(cb, true);

    /*Align the container to the middle*/
    lv_obj_align(cont, NULL, LV_ALIGN_IN_RIGHT_MID, -15, -20);

    cont = lv_cont_create(lv_scr_act(), NULL);
    lv_cont_set_layout(cont, LV_LAYOUT_COL_L); /*Arrange the children in a column*/
    lv_cont_set_fit(cont, true, true);         /*Fit the size to the content*/
    lv_obj_set_style(cont, &style_border);

    cb = lv_cb_create(cont, NULL);
    lv_cb_set_text(cb, "");
    lv_cb_set_action(cb, enableHardRoller);

    lv_cb_set_checked(cb, true);

    lv_obj_align(cont, NULL, LV_ALIGN_IN_RIGHT_MID, -15, 75);

    static lv_point_t line_points[] = {{0, 45}, {480, 45}};
    lv_obj_t *line;
    line = lv_line_create(lv_scr_act(), NULL);
    lv_line_set_points(line, line_points, 2); /*Set the points*/
    lv_obj_align(line, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

    static lv_point_t line_points2[] = {{280, 45}, {280, 240}};
    line = lv_line_create(lv_scr_act(), NULL);
    lv_line_set_points(line, line_points2, 2); /*Set the points*/
    lv_obj_align(line, NULL, LV_ALIGN_CENTER, 0, 0);

    static lv_point_t line_points3[] = {{0, 45}, {0, 240}};
    line = lv_line_create(lv_scr_act(), NULL);
    lv_line_set_points(line, line_points3, 2); /*Set the points*/
    lv_obj_align(line, NULL, LV_ALIGN_CENTER, -60, 0);

    pros::delay(50);
}
