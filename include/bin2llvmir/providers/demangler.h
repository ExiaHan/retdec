/**
 * @file include/bin2llvmir/providers/demangler.h
 * @brief Demangler provider for bin2llvmirl.
 * @copyright (c) 2017 Avast Software, licensed under the MIT license
 */

#ifndef BIN2LLVMIR_PROVIDERS_DEMANGLER_H
#define BIN2LLVMIR_PROVIDERS_DEMANGLER_H

#include <map>

#include <llvm/IR/Module.h>

#include "retdec-config/tool_info.h"
#include "demangler/demangler.h"

namespace bin2llvmir {

/**
 * Completely static object -- all members and methods are static -> it can be
 * used by anywhere in bin2llvmirl. It provides mapping of modules to demanglers
 * associated with them.
 *
 * @attention Even though this is accessible anywhere in bin2llvmirl, use it only
 * in LLVM passes' prologs to initialize pass-local demangler object. All
 * analyses, utils and other modules *MUST NOT* use it. If they need to work
 * with demangler, they should accept it in parameter.
 */
class DemanglerProvider
{
	public:
		static demangler::CDemangler* addDemangler(
				llvm::Module* m,
				const retdec_config::ToolInfoContainer& t);

		static demangler::CDemangler* getDemangler(llvm::Module* m);
		static bool getDemangler(
				llvm::Module* m,
				demangler::CDemangler*& d);

		static void clear();

	private:
		using Demangler = std::unique_ptr<demangler::CDemangler>;
		/// Mapping of modules to demanglers associated with them.
		static std::map<llvm::Module*, Demangler> _module2demangler;
};

} // namespace bin2llvmir

#endif
