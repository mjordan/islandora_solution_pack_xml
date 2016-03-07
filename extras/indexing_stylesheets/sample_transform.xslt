<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:xlink="http://www.w3.org/1999/xlink"
  xmlns:foxml="info:fedora/fedora-system:def/foxml#">

  <xsl:template match="foxml:datastream[@ID='OBJ']/foxml:datastreamVersion[last() and @MIMETYPE='application/xml']" name="index_simple_xml_sp">
    <xsl:param name="content"/>
    <xsl:param name="prefix">islandora_simple_xml_sp_</xsl:param>
    <xsl:param name="suffix">_ms</xsl:param>

    <!-- This select expression gets all the granchildren of the $content context,
         i.e., all children of the document element. -->
    <xsl:for-each select="$content/*/*">
      <field>
        <xsl:attribute name="name">
          <xsl:value-of select="concat($prefix, local-name(), $suffix)"/>
        </xsl:attribute>
        <xsl:value-of select="text()"/>
      </field>
    </xsl:for-each>
  </xsl:template>
</xsl:stylesheet>
