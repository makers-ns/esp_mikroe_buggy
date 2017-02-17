/*********************************************************************************
  Copyright (c) 2017 ChedaDSP@Makers-NS. All right reserved.

  esp2866 as web controller for MikroE Buggy

  This is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*****************************************************************************/
#define THROTTLE_TRESHOLD 30
#define THROTTLE_MAX 90
#define PWM_MIN 190
#define PWM_MAX 1023
#define DIRECTION_TRESHOLD 30
#define FULL_PWM_FACTOR 2.55

void setupBuggy();
void stopBuggy();
void moveBuggy(int direction, int throttle);
