# Game data worker

`workers/content` is the only reader of the private R2 bucket. `GET /files/<name>` streams one freeware file and honors a `Range` header, so a download can resume. `GET /manifest.json` returns the bucket object `manifest.json`.

`bucket_name` in `wrangler.jsonc` is the existing bucket. The names the worker will serve are the `files` list in `manifest.json` in this directory. A request for any other name is refused before the rate limit is counted.

Each address is limited to 100 requests in 60 seconds at one Cloudflare location. That limit is not a daily cap, and a burst can pass it. The worker logs the client `User-Agent` and does not check it.

From this directory:

```
npx wrangler deploy
```

Set `Content_Download_Root()` in `code/contentcatalog.cpp` to the origin that command prints. The client calls `/files/<name>` on that origin.
