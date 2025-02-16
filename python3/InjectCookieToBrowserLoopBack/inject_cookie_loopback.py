import sys
import http.server
from urllib.parse import urlparse, parse_qs

PORT = 4200

class SimpleHTTPRequestHandler(http.server.BaseHTTPRequestHandler):
    def __init__(self, cookies, *args, **kwargs):
        self.cookies = cookies
        super().__init__(*args, **kwargs)

    def do_GET(self):
        # Parse URL parameters
        query_components = parse_qs(urlparse(self.path).query)

        # Check for required parameters
        nonce = query_components.get('nonce', [None])[0]
        redirect_url = query_components.get('redirect_url', [None])[0]

        if nonce and redirect_url:
            self.send_response(302)
            self.send_header('Location', redirect_url)
        else:
            self.send_response(400)
            self.send_header('Content-type', 'text/html')
            self.wfile.write(b'Missing nonce or redirect_url parameter')

        # Inject cookies
        for cookie in self.cookies:
            self.send_header('Set-Cookie', cookie)

        self.end_headers()


def run(server_class=http.server.HTTPServer, handler_class=SimpleHTTPRequestHandler, cookies=None):
    if cookies is None:
        cookies = []

    def handler(*args, **kwargs) -> SimpleHTTPRequestHandler:
        return handler_class(cookies, *args, **kwargs)

    server_address = ('', 8000)
    httpd = server_class(server_address, handler)
    print('Starting httpd on port 8000...')
    httpd.serve_forever()

def main(args : list[str]) :

    # Note : It's impossible to inject cookies for another domain (which was the exercise for this piece of code)
    # So, it's valuable to process some stuff, but unusable to inject cookies for another domain.

    cookies = [
    ]

    run(cookies=cookies)

if __name__ == "__main__" :
    exit(main(sys.argv[1:]))