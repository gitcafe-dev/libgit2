#include "clar_libgit2.h"
#include "submodule_helpers.h"
#include "git2/sys/repository.h"
#include "repository.h"
#include "fileops.h"

static git_repository *g_repo = NULL;

void test_submodule_lookupbare__initialize(void)
{
	g_repo = cl_git_sandbox_init("submod2.git");
}

void test_submodule_lookupbare__simple_lookup(void)
{
	git_tree *tree;
	get_tree_from_branch(&tree, g_repo, "master");

	assert_submodule_exists_on(g_repo, "sm_unchanged", tree);
	assert_submodule_exists_on(g_repo, "sm_missing_commits", tree);
	assert_submodule_exists_on(g_repo, "sm_changed_file", tree);
	assert_submodule_exists_on(g_repo, "sm_changed_index", tree);
	assert_submodule_exists_on(g_repo, "sm_changed_head", tree);
	assert_submodule_exists_on(g_repo, "sm_changed_untracked_file", tree);

	/* lookup pending change in .gitmodules that is not in HEAD */
	refute_submodule_exists_on(g_repo, "sm_added_and_uncommited", tree, GIT_ENOTFOUND);

	/* lookup git repo subdir that is not added as submodule */
	refute_submodule_exists_on(g_repo, "not-submodule", tree, GIT_ENOTFOUND);

	/* lookup existing directory that is not a submodule */
	refute_submodule_exists_on(g_repo, "just_a_dir", tree, GIT_ENOTFOUND);

	/* lookup existing file that is not a submodule */
	refute_submodule_exists_on(g_repo, "just_a_file", tree, GIT_ENOTFOUND);

	/* lookup non-existent item */
	refute_submodule_exists_on(g_repo, "no_such_file", tree, GIT_ENOTFOUND);
}
