#include <napi.h>

#include <unistd.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <sys/syslimits.h>

Napi::Value currentUserIsAdmin(const Napi::CallbackInfo &info)
{
  // A user cannot be member in more than NGROUPS_MAX groups,
  // not counting the default group (hence the + 1)
  gid_t groupIDs[NGROUPS_MAX + 1];
  // ID of user who started the process
  uid_t userID = getuid();
  // Get user password info for that user
  struct passwd *pw = getpwuid(userID);

  int groupCount;
  if (pw)
  {
    // Look up groups that user belongs to
    groupCount = NGROUPS_MAX + 1;
    // getgrouplist returns ints and not gid_t and
    // both may not necessarily have the same size
    int intGroupIDs[NGROUPS_MAX + 1];
    getgrouplist(pw->pw_name, pw->pw_gid, intGroupIDs, &groupCount);
    // Copy them to real array
    for (int i = 0; i < groupCount; i++)
      groupIDs[i] = intGroupIDs[i];
  }
  else
  {
    // We cannot lookup the user but we can look what groups this process
    // currently belongs to (which is usually the same group list).
    groupCount = getgroups(NGROUPS_MAX + 1, groupIDs);
  }

  for (int i = 0; i < groupCount; i++)
  {
    // Get the group info for each group
    struct group *group = getgrgid(groupIDs[i]);
    if (!group)
      continue;
    // An admin user is member of the group named "admin"
    if (strcmp(group->gr_name, "admin") == 0)
      return Napi::Value::From(info.Env(), true);
  }
  return Napi::Value::From(info.Env(), false);
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(Napi::String::New(env, "currentUserIsAdmin"), Napi::Function::New(env, currentUserIsAdmin));
  return exports;
}
#if NODE_MAJOR_VERSION >= 10
NAN_MODULE_WORKER_ENABLED(currentUserIsAdminModule, Init)
#else
NODE_API_MODULE(currentUserIsAdminModule, Init);
#endif