// Originally released under a custom license.
// This historical re-release is provided under the MIT License.
// See the LICENSE file in the repo root for details.
//
// https://github.com/nettlep
//
// Call into the DLL to display the dialog

extern "C"{
 __declspec( dllimport ) bool WINAPI FSColorPickerDoModal(unsigned int * currentColor, const bool currentColorIsDefault, unsigned int * originalColor, const bool originalColorIsDefault, const int initialExpansionState);
};

// Initial expansion states:

#define FSCOLOR_DEFAULT    0// - use defaults
#define FSCOLOR_EXP1_BTN1  1// - force expanded    show expansion button
#define FSCOLOR_EXP1_BTN0  2// - force expanded    hide the expansion button
#define FSCOLOR_EXP0_BTN1  3// - force compressed  show expansion button
#define FSCOLOR_EXP0_BTN0  4// - force compressed  hide expansion button

