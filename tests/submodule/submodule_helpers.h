extern void rewrite_gitmodules(const char *workdir);

/* these will automatically set a cleanup callback */
extern git_repository *setup_fixture_submodules(void);
extern git_repository *setup_fixture_submod2(void);
extern git_repository *setup_fixture_submodule_simple(void);
extern git_repository *setup_fixture_super(void);

extern unsigned int get_submodule_status(git_repository *, const char *);

extern void assert__submodule_exists(
	git_repository *, const char *, const char *, const char *, int);
extern void assert__submodule_exists_on(
    git_repository *, const char *, git_tree *, const char *, const char *, int);

#define assert_submodule_exists(repo,name)								\
	assert__submodule_exists(repo, name, "git_submodule_lookup(" #name ") failed", __FILE__, __LINE__)

#define assert_submodule_exists_on(repo,name,tree)                      \
    assert__submodule_exists_on(repo, name, tree, "git_submodule_lookup_from_tree(" #name ") failed", __FILE__, __LINE__)

extern void refute__submodule_exists(
	git_repository *, const char *, int err, const char *, const char *, int);

extern void refute__submodule_exists_on(
    git_repository *, const char *, git_tree *, int err, const char *, const char *, int);

#define refute_submodule_exists(repo,name,code) \
	refute__submodule_exists(repo, name, code, "expected git_submodule_lookup(" #name ") to fail with error " #code, __FILE__, __LINE__)

#define refute_submodule_exists_on(repo,name,tree,code) \
    refute__submodule_exists_on(repo, name, tree, code, "expected git_submodule_lookup_from_tree(" #name ") to fail with error " #code, __FILE__, __LINE__)

extern void dump_submodules(git_repository *repo);
extern void get_tree_from_branch(git_tree **tree, git_repository *repo, const char *branch_name);
