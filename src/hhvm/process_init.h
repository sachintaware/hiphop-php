/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010- Facebook, Inc. (http://www.facebook.com)         |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/
#ifndef incl_HHVM_PROCESS_INIT_H_
#define incl_HHVM_PROCESS_INIT_H_

#include "util/base.h"
#include "runtime/base/thread_init_fini.h"

namespace HPHP {

extern void (*g_vmProcessInit)();
void hphp_process_init();

namespace VM {
  void ProcessInit();
  void initialize_repo();
}

/*
 * This must be called before execute_program_impl in an hhvm build.
 */
inline void register_process_init() {
  if (hhvm) g_vmProcessInit = &VM::ProcessInit;
}

/*
 * Initialize the runtime in a way that's appropriate for unit tests
 * that make partial use of libhphp_runtime.a.  (There will not be a
 * real execution context or anything like that.)
 */
inline void init_for_unit_test() {
  register_process_init();
  if (hhvm) VM::initialize_repo();
  init_thread_locals();
  Hdf config;
  RuntimeOption::Load(config);
  hphp_process_init();
}

}

#endif