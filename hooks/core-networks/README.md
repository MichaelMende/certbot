### Hook for Core-Networks.de's DNS API

```bash
export CORE_API_LOGIN=me
export CORE_API_PASSWORD=mypassword

sudo certbot --manual-auth-hook hooks/core-networks/authenticator.sh --manual-cleanup-hook hooks/core-networks/cleanup.sh ...
```
