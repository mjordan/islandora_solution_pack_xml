<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <xsl:template match="/book/chapter/title">
  <xsl:param name="table_of_contents"></xsl:param>
    <p>xsl:value-of select="."/></p>
  </xsl:template>

</xsl:stylesheet>
