
# Build image from a minimal, pinned base OS to avoid using pre-built application images.
# This allows full control over what is installed, and ensures reproducible builds.
ARG BASE_OS=debian:12-slim
FROM ${BASE_OS}

# Install nginx from the distribution packages. We update apt lists, install nginx,
# then clean apt cache to reduce image size.
 RUN apt-get update \
 && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
 	 nginx \
 	 curl \
 && rm -rf /var/lib/apt/lists/*

# Copy site configuration and static files into the image. These files are used by nginx
# to serve content. During development we also mount the same folder as a volume so local
# changes are visible immediately; the COPY ensures a default is present in the image.
COPY ./conf/default /etc/nginx/conf.d/default.conf


# Expose only port 443 for HTTPS traffic (TLSv1.2/1.3)
EXPOSE 443

# Run nginx in the foreground so the container keeps running. We don't use a service manager
# inside the container; running the daemon in the foreground is the standard pattern.
CMD ["nginx", "-g", "daemon off;"]
