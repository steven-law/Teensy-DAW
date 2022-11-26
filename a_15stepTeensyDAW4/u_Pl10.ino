void Plugin_10_Settings() {
  //place here the Audio settings for your plugin
}

void Plugin10_Page_Static(byte Pagenumber) {
  //place here the (copied!) shown controls for your plugin
  //if needed draw selecting pages buttons
  //draw_sub_page_buttons(n); //max 4
}

void Plugin10_Page1_Dynamic() {
  switch (lastPotRow) {
    case 0:
      if (millis() % 20 > 15) {
      }
      break;
    case 1:
      if (millis() % 20 > 15) {
      }
      break;
    case 2:
      if (millis() % 20 > 15) {
      }
      break;
    case 3:
      if (millis() % 20 > 15) {
      }
      break;
  }
  if (ts.touched()) {
    if (gridTouchY >= 2 && gridTouchY <= 4) {
      lastPotRow = 0;
    }

    if (gridTouchY >= 5 && gridTouchY <= 7) {
      lastPotRow = 1;
    }

    if (gridTouchY >= 8 && gridTouchY <= 10) {
      lastPotRow = 2;
    }
    if (gridTouchY >= 11 && gridTouchY <= 13) {
      lastPotRow = 3;
    }
  }
}
