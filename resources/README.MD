# HOW TO USE
- use `domain-match` and `domain-exclude` to find the ISP
- if can not find the ISP, then search the mx of the domain from the internet and use `mx-match` to match the ISP(email enterprise)
- There are several other field which is useful
  - alias support（two fields: `alias-help-page` & `alias-support`)
    some ISP support alias while some are not
  - auto-copy-to-sent(Deprecated)
    we should not depend on this for it can be changed by the user in some ISPs. 
  - mailboxes(Deprecated)
    we should not depend on this for it will change when the langudge changes in some ISPs.