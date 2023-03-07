static const struct s_builtins  g_builtins[] =
    {
        {"echo", echo_builtin},
        {"cd", cd_builtin},
        {"pwd", pwd_builtin},
        {"env", env_builtin},
        {"export", export_builtin},
        {"unset", unset_builtin},
        {NULL, NULL}
    }

